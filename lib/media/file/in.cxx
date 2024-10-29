#include "in.hxx"
#include "../audio/codec.hxx"
#include "../audio/stream.hxx"
#include "../video/codec.hxx"
#include "../video/hdr10.hxx"
#include "../video/stream.hxx"
#include "../subtitle/codec.hxx"
#include "../subtitle/stream.hxx"
#include "../../system/executable/ffmpeg.hxx"
#include "../../system/executable/ffprobe.hxx"
#include "../../system/executable/hdr10plus.hxx"

#include <sstream>

using namespace Alchemist::Media;

InFile::InFile(const std::filesystem::path& filename):File(filename) { InitStreams(); }

InFile::InFile(std::filesystem::path&& filename):File(std::move(filename)) { InitStreams(); }

void InFile::InitStreams() {
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

std::shared_ptr<Stream> InFile::ParseAudioInfo(const Json::Value& json_part) {
	std::shared_ptr<Audio::Stream> stream = std::make_shared<Audio::Stream>(json_part["index"].asUInt());
	std::shared_ptr<Codec> codec;
	unsigned short channels, sample_rate;
	for (auto it = json_part.begin(); it != json_part.end(); it++) {
		if (it.key() == "codec_name" && Audio::Codec::All.contains(it->asString()))
			codec = Audio::Codec::All.at(it->asString());
		else if (it.key() == "channels")
			channels = std::stoul(it->asString()); //JsonCPP bug converting to uint
		else if (it.key() == "sample_rate")
			sample_rate = std::stoul(it->asString()); //JsonCPP bug converting to uint
	}
	stream->SetCodec(codec);
	stream->SetMetadata({sample_rate, channels});
	return stream;
}

std::shared_ptr<Stream> InFile::ParseVideoInfo(const Json::Value& json_part) {
	std::shared_ptr<Video::Stream> stream = std::make_shared<Video::Stream>(json_part["index"].asUInt());
	std::shared_ptr<Codec> codec;
	Video::Metadata metadata;
	Video::Color color;
	unsigned short width, height;
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
	}
	stream->SetCodec(codec);
	metadata.SetResolution({width, height});

	// Check for HDR10 information only if neccesary
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

std::shared_ptr<Stream> InFile::ParseSubtitleInfo(const Json::Value& json_part) {
	std::shared_ptr<Subtitle::Stream> stream = std::make_shared<Subtitle::Stream>(json_part["index"].asUInt());
	std::shared_ptr<Codec> codec;
	for (auto it = json_part.begin(); it != json_part.end(); it++)
		if (it.key() == "codec_name" && Subtitle::Codec::All.contains(it->asString()))
			codec = Subtitle::Codec::All.at(it->asString());
	stream->SetCodec(codec);
	return stream;
}

std::shared_ptr<Video::HDR10> InFile::GetHDR10Info() {
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
		std::pair<std::optional<unsigned short>, std::optional<unsigned short>> red, green, blue, white;
		std::pair<std::optional<unsigned short>, std::optional<unsigned int>> luminance;
		std::pair<std::optional<unsigned short>, std::optional<unsigned short>> light_level;

		for (Json::ArrayIndex i = 0; i < videoinfo_json.size(); i++) {
			for (auto it = videoinfo_json[i].begin(); it != videoinfo_json[i].end(); it++) {
				if (videoinfo_json[i].find("side_data_type")) {
					if (videoinfo_json[i].find("side_data_type")->asString() == "Mastering display metadata") {
						// Main HDR10 info
						if (it.key() == "blue_x")
							blue.first = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "blue_y")
							blue.second = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "green_x")
							green.first = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "green_y")
							green.second = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "red_x")
							red.first = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "red_y")
							red.second = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "white_point_x")
							white.first = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "white_point_y")
							white.second = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "min_luminance")
							luminance.first = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "max_luminance")
							luminance.second = std::stoul(SplitString(it->asString())[0]);
					}
					else if (videoinfo_json[i].find("side_data_type")->asString() == "Content light level metadata") {
						// Extra optional light level data
						if (it.key() == "max_content")
							light_level.first = std::stoul(SplitString(it->asString())[0]);
						else if (it.key() == "max_average")
							light_level.second = std::stoul(SplitString(it->asString())[0]);
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

bool InFile::HasHDR10Plus() {
	auto ffmpeg = System::FFmpeg::hdr_stream(m_filename);
	auto hdr10plus = System::HDR10Plus::hdr_plus_detect();
	std::string buffer;

	*ffmpeg >> *hdr10plus;
	*hdr10plus >> buffer;
	int status = hdr10plus->wait();
	ffmpeg->wait();

	return status == 0;
}

std::vector<std::string> InFile::SplitString(const std::string& str) const {
	std::vector<std::string> strings;
    std::istringstream f(str);
    std::string s;    
    while (std::getline(f, s, '/')) {
        strings.push_back(s);
    }
	return strings;
}