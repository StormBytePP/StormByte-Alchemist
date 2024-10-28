#include "in.hxx"
#include "../audio/stream.hxx"
#include "../video/stream.hxx"
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
			const std::string stream_type = stream_json[i].find("codec_type")->asString();
			std::shared_ptr<Stream> stream;
			if (stream_type == "audio")
				stream = ParseAudioInfo(stream_json[i]);
			else if (stream_type == "video")
				stream = ParseAudioInfo(stream_json[i]);
			else if (stream_type == "subtitle")
				stream = ParseAudioInfo(stream_json[i]);

			// Language, title ("tags"), default and forced ("disposition") are general data for all stream types:
			Json::Value disposition = stream_json[i].find("disposition");
			if (disposition) {
				if (disposition.find("default"))
					stream->SetDefaultStatus(disposition.find("default")->asBool());
				if (disposition.find("forced"))
					stream->SetDefaultStatus(disposition.find("forced")->asBool());
			}
			Json::Value tags = stream_json[i].find("tags");
			if (tags) {
				if (tags.find("language"))
					stream->SetLanguage(tags.find("language")->asString());
				if (tags.find("title"))
					stream->SetTitle(tags.find("title")->asString());
			}
			m_streams.push_back({stream, i});
		}
	}
}

std::shared_ptr<Stream> InFile::ParseAudioInfo([[maybe_unused]]const Json::Value& json_part) {
	std::shared_ptr<Audio::Stream> stream = std::make_shared<Audio::Stream>();
	for (auto it = json_part.begin(); it != json_part.end(); it++) {
	}
	return stream;
}

std::shared_ptr<Stream> InFile::ParseVideoInfo([[maybe_unused]]const Json::Value& json_part) {
	std::shared_ptr<Video::Stream> stream = std::make_shared<Video::Stream>();
	for (auto it = json_part.begin(); it != json_part.end(); it++) {
	}
	return stream;
}

std::shared_ptr<Stream> InFile::ParseSubtitleInfo([[maybe_unused]]const Json::Value& json_part) {
	std::shared_ptr<Subtitle::Stream> stream = std::make_shared<Subtitle::Stream>();
	for (auto it = json_part.begin(); it != json_part.end(); it++) {
	}
	return stream;
}