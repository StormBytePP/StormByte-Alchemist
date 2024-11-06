#include <Alchemy/media/file.hxx>
#include <Alchemy/media/audio/codec.hxx>
#include <Alchemy/media/audio/stream.hxx>
#include <Alchemy/media/video/codec.hxx>
#include <Alchemy/media/video/hdr10.hxx>
#include <Alchemy/media/video/stream.hxx>
#include <Alchemy/media/subtitle/codec.hxx>
#include <Alchemy/media/subtitle/stream.hxx>
#include <Alchemy/system/executable/ffmpeg.hxx>
#include <Alchemy/system/executable/ffprobe.hxx>
#include <Alchemy/system/executable/hdr10plus.hxx>

#include <sstream>

using namespace Alchemist::Media;

File::File(const std::filesystem::path& filename):m_filename(filename) { InitStreams(); }

File::File(std::filesystem::path&& filename):m_filename(std::move(filename)) { InitStreams(); }

const std::filesystem::path& File::GetFileName() const noexcept { return m_filename; }

const std::vector<std::shared_ptr<Stream>>& File::GetStreams() const noexcept { return m_streams; }

const uint64_t& File::GetSize() const noexcept { return m_size_bytes; }

void File::InitStreams() {
	if (!std::filesystem::exists(m_filename))
		return;

	std::unique_ptr<System::FFprobe> probe;
	std::string buffer;
	Json::Reader reader;
    Json::Value root;

	/* Getting FFprobe data in Json*/
	probe = System::FFprobe::all_info(m_filename);
	probe->wait();
	*probe >> buffer;

	/* Parse Json */
	reader.parse(buffer, root, false);
	if (root.size() > 0) {
		auto stream_json = root["streams"];
		for (Json::ArrayIndex i = 0; i < stream_json.size(); i++) {
			m_streams.reserve(stream_json.size());
			const std::string stream_type = stream_json[i].find("codec_type")->asString();
			std::shared_ptr<Stream> stream;
			if (stream_type == "audio")
				stream = ParseAudioInfo(stream_json[i]);
			else if (stream_type == "video")
				stream = ParseVideoInfo(stream_json[i]);
			else if (stream_type == "subtitle")
				stream = ParseSubtitleInfo(stream_json[i]);

			// Language, title ("tags"), default and forced ("disposition") are general data for all stream types:
			if (stream_json[i].isMember("disposition")) {
				if (stream_json[i]["disposition"].isMember("default"))
					stream->SetDefaultStatus(stream_json[i]["disposition"].find("default")->asBool());
				if (stream_json[i]["disposition"].isMember("forced"))
					stream->SetDefaultStatus(stream_json[i]["disposition"].find("forced")->asBool());
			}
			if (stream_json[i].isMember("tags")) {
				if (stream_json[i]["tags"].isMember("language"))
					stream->SetLanguage(stream_json[i]["tags"].find("language")->asString());
				if (stream_json[i]["tags"].isMember("title"))
					stream->SetTitle(stream_json[i]["tags"].find("title")->asString());
			}
			m_streams.push_back(stream);
		}
	}
}

std::shared_ptr<Stream> File::ParseAudioInfo(const Json::Value& json_part) {
	std::shared_ptr<Audio::Stream> stream = std::make_shared<Audio::Stream>(json_part["index"].asUInt());
	std::shared_ptr<Codec> codec;
	int channels, sample_rate;
	for (auto it = json_part.begin(); it != json_part.end(); it++) {
		if (it.key() == "codec_name" && Audio::Codec::All.contains(it->asString()))
			codec = Audio::Codec::All.at(it->asString());
		else if (it.key() == "channels")
			channels = static_cast<int>(std::stoul(it->asString())); //JsonCPP bug converting to uint and Windows needs the cast
		else if (it.key() == "sample_rate")
			sample_rate = static_cast<int>(std::stoul(it->asString())); //JsonCPP bug converting to uint and Windows needs the cast
	}
	stream->SetCodec(codec);
	stream->SetMetadata({sample_rate, channels});
	return stream;
}

std::shared_ptr<Stream> File::ParseVideoInfo(const Json::Value& json_part) {
	std::shared_ptr<Video::Stream> stream = std::make_shared<Video::Stream>(json_part["index"].asUInt());
	std::shared_ptr<Codec> codec;
	Video::Metadata metadata;
	Video::Color color;
	int width, height;
	for (auto it = json_part.begin(); it != json_part.end(); it++) {
		if (it.key() == "codec_name" && Video::Codec::All.contains(it->asString()))
			codec = Video::Codec::All.at(it->asString());
		else if (it.key() == "width")
			width = it->asUInt();
		else if (it.key() == "height")
			height = it->asUInt();
		else if (it.key() == "color_space")
			color.SetMatrix(it->asString());
		else if (it.key() == "color_transfer")
			color.SetTransfer(it->asString());
		else if (it.key() == "color_transfer")
			color.SetTransfer(it->asString());
		else if (it.key() == "color_primaries")
			color.SetPrimaries(it->asString());
		else if (it.key() == "pix_fmt")
			color.SetPixelFormat(it->asString());
		else if (it.key() == "tags") {
			if (it->find("NUMBER_OF_FRAMES")) {
				metadata.SetFrames(std::stoul(it->find("NUMBER_OF_FRAMES")->asString()));
			}
		}
		else if (it.key() == "nb_frames")
			metadata.SetFrames(std::stoul(it->asString()));
	}
	stream->SetCodec(codec);
	metadata.SetResolution({width, height});

	/* If we could not obtain frame number we will need to look for it (long operation!) */
	/* We will only do this if the codec is valid */
	if (stream->GetCodec() && !metadata.GetFrames())
		metadata.SetFrames(CountVideoFrames());

	/* Check for HDR10 information only if neccesary */
	if (color.IsHDR10()) {
		std::shared_ptr<Video::HDR10> hdr10info = GetHDR10Info();

		/* Some videos contain the correct HDR10 color modes but lack for metadata *
		*  so in those cases we put a default metadata on them so they can be displayed as HDR10 */
		hdr10info = hdr10info ? hdr10info : std::make_shared<Video::HDR10>(Video::HDR10::DEFAULT);

		/* Finally we search if we have HDR10+ data in */
		if (HasHDR10Plus())
			hdr10info->SetPlusFile("yes"); /* This is only to indicate we have, it will be replaced by correct file by converter */

		metadata.SetHDR10(*hdr10info);
	}
	metadata.SetColor(std::move(color));
	stream->SetMetadata(std::move(metadata));
	return stream;
}

std::shared_ptr<Stream> File::ParseSubtitleInfo(const Json::Value& json_part) {
	std::shared_ptr<Subtitle::Stream> stream = std::make_shared<Subtitle::Stream>(json_part["index"].asUInt());
	std::shared_ptr<Codec> codec;
	for (auto it = json_part.begin(); it != json_part.end(); it++)
		if (it.key() == "codec_name" && Subtitle::Codec::All.contains(it->asString()))
			codec = Subtitle::Codec::All.at(it->asString());
	stream->SetCodec(codec);
	return stream;
}

std::shared_ptr<Video::HDR10> File::GetHDR10Info() {
	std::shared_ptr<Video::HDR10> hdr10info;
	std::unique_ptr<System::FFprobe> probe;
	std::string buffer;
	Json::Reader reader;
    Json::Value root;

	/* Getting FFprobe data in Json*/
	probe = System::FFprobe::hdr10_info(m_filename);
	probe->wait();
	*probe >> buffer;

	/* Parse Json */
	reader.parse(buffer, root, false);
	if (root.size() > 0) {
		auto videoinfo_json = root["frames"][0]["side_data_list"];
		std::pair<std::optional<int>, std::optional<int>> red, green, blue, white;
		std::pair<std::optional<int>, std::optional<unsigned int>> luminance;
		std::pair<std::optional<int>, std::optional<int>> light_level;

		for (Json::ArrayIndex i = 0; i < videoinfo_json.size(); i++) {
			for (auto it = videoinfo_json[i].begin(); it != videoinfo_json[i].end(); it++) {
				if (videoinfo_json[i].find("side_data_type")) {
					if (videoinfo_json[i].find("side_data_type")->asString() == "Mastering display metadata") {
						// Main HDR10 info
						// The static casts are to silence Windows warnings
						if (it.key() == "blue_x")
							blue.first = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "blue_y")
							blue.second = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "green_x")
							green.first = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "green_y")
							green.second = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "red_x")
							red.first = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "red_y")
							red.second = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "white_point_x")
							white.first = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "white_point_y")
							white.second = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "min_luminance")
							luminance.first = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "max_luminance")
							luminance.second = std::stoul(SplitString(it->asString())[0]);
					}
					else if (videoinfo_json[i].find("side_data_type")->asString() == "Content light level metadata") {
						// Extra optional light level data
						if (it.key() == "max_content")
							light_level.first = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
						else if (it.key() == "max_average")
							light_level.second = static_cast<int>(std::stoul(SplitString(it->asString())[0]));
					}
					// The rest is ignored
				}
			}

			// Now check if the gathered data is valid
			if (red.first && red.second && green.first && green.second && blue.first && blue.second
				&& white.first && white.second && luminance.first && luminance.second) {
				Video::HDR10 hdr10_data(
					{	*red.first, 		*red.second		},
					{	*green.first, 		*green.second		},
					{	*blue.first, 		*blue.second		},
					{	*white.first, 		*white.second		},
					{	*luminance.first,	*luminance.second	}
				);

				if (light_level.first && light_level.second)
					hdr10_data.SetLightLevel({*light_level.first, *light_level.second});

				hdr10info = std::make_shared<Video::HDR10>(std::move(hdr10_data));
			}
		}
	}

	return hdr10info;
}

bool File::HasHDR10Plus() {
	auto ffmpeg = System::FFmpeg::hdr_stream(m_filename);
	auto hdr10plus = System::HDR10Plus::hdr_plus_detect();
	std::string buffer;

	*ffmpeg >> *hdr10plus;
	*hdr10plus >> buffer;
	int status = hdr10plus->wait();
	ffmpeg->wait();

	return status == 0;
}

unsigned int File::CountVideoFrames() {
	auto ffprobe = System::FFprobe::count_video_frames(m_filename);
	std::string buffer;
	Json::Reader reader;
    Json::Value root;

	*ffprobe >> buffer;
	ffprobe->wait();

	reader.parse(buffer, root, false);
	return std::stoul(root["streams"][0]["nb_read_packets"].asString());
}

std::vector<std::string> File::SplitString(const std::string& str) const {
	std::vector<std::string> strings;
    std::istringstream f(str);
    std::string s;    
    while (std::getline(f, s, '/')) {
        strings.push_back(s);
    }
	return strings;
}