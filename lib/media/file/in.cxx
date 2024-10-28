#include "in.hxx"
#include "../audio/codec.hxx"
#include "../audio/stream.hxx"
#include "../video/codec.hxx"
#include "../video/stream.hxx"
#include "../subtitle/codec.hxx"
#include "../subtitle/stream.hxx"
#include "../../system/executable/ffprobe.hxx"

using namespace Alchemist::Media;

InFile::InFile(const std::filesystem::path& filename):File(filename) { InitStreams(); }

InFile::InFile(std::filesystem::path&& filename):File(std::move(filename)) { InitStreams(); }

void InFile::InitStreams() {
	/** To be done later **/
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
	std::cout << "Parsing audio info..." << std::endl;
	unsigned short channels, sample_rate;
	for (auto it = json_part.begin(); it != json_part.end(); it++) {
		if (it.key() == "codec_name") {
			std::cout << "Looking for codec: '" << it->asString() << "'" << std::endl;
			codec = Audio::Codec::All.at(it->asString());
		}
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
	std::cout << "Parsing video info..." << std::endl;
	unsigned short width, height;
	for (auto it = json_part.begin(); it != json_part.end(); it++) {
		if (it.key() == "codec_name") {
			std::cout << "Looking for codec: '" << it->asString() << "'" << std::endl;
			codec = Video::Codec::All.at(it->asString());
		}
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
	metadata.SetColor(std::move(color));
	stream->SetMetadata(std::move(metadata));
	return stream;
}

std::shared_ptr<Stream> InFile::ParseSubtitleInfo(const Json::Value& json_part) {
	std::shared_ptr<Subtitle::Stream> stream = std::make_shared<Subtitle::Stream>(json_part["index"].asUInt());
	std::shared_ptr<Codec> codec;
	std::cout << "Parsing subtitle info..." << std::endl;
	for (auto it = json_part.begin(); it != json_part.end(); it++)
		if (it.key() == "codec_name")
			codec = Subtitle::Codec::All.at(it->asString());
	stream->SetCodec(codec);
	return stream;
}