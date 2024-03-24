#include "infile.hxx"

#include "../codec/audio/unknown.hxx"
#include "../codec/video/unknown.hxx"
#include "../codec/subtitle/unknown.hxx"
#include "../../system/executable/ffmpeg.hxx"
#include "../../system/executable/ffprobe.hxx"
#include "../../system/executable/hdr10plus.hxx"

#include <fstream>
#include <json/json.h>

Alchemist::Media::File::InFile::InFile(const std::filesystem::path& file_path):Base(file_path) {
	update();
}

Alchemist::Media::File::InFile::InFile(std::filesystem::path&& file_path):Base(std::move(file_path)) {
	update();
}

void Alchemist::Media::File::InFile::update() {
	m_features 	= 0;
	m_status 	= 0;

	update_readability();

	if (m_status == Status::OK) {
		update_features();
		update_streams();
	}
}

void Alchemist::Media::File::InFile::update_readability() {
	if (!std::filesystem::exists(m_media_path) || !std::filesystem::is_regular_file(m_media_path)) {
		m_status |= Status::NOT_EXISTS;
	}
	else {
		std::ifstream file(m_media_path);
		if (!file.good()) {
			m_status |= Status::NOT_READABLE;
		}
	}
}

void Alchemist::Media::File::InFile::update_features() {
	std::unique_ptr<System::FFprobe> ffprobe;
	std::unique_ptr<System::FFmpeg> ffmpeg;
	std::unique_ptr<System::HDR10Plus> hdr10plus_tool;
	std::string buffer;

	// Checking for HDR
	ffprobe = System::FFprobe::video_info(m_media_path);
	*ffprobe >> buffer;
	ffprobe->wait();
	ffprobe.reset();

	Json::Value root;
    Json::Reader reader;
    if (reader.parse(buffer, root)) {
		if ((root["streams"][0]["color_transfer"] == "smpte2084") || (root["streams"][0]["color_transfer"] == "arib-std-b67")) {
			m_features |= Feature::HDR;
			buffer = "";
			ffmpeg = System::FFmpeg::hdr_plus(m_media_path);
			hdr10plus_tool = System::HDR10Plus::hdr_plus_detect();
			*ffmpeg >> *hdr10plus_tool;
			ffmpeg->wait();
			int result = hdr10plus_tool->wait();
			*hdr10plus_tool >> buffer;
			ffmpeg.reset();
			hdr10plus_tool.reset();
			if (result == 0) m_features |= Feature::HDR_PLUS;
		}
	}
}

void Alchemist::Media::File::InFile::update_streams() {
	m_streams.clear();

	std::unique_ptr<System::FFprobe> ffprobe;
	std::string buffer;

	ffprobe = System::FFprobe::all_info(m_media_path);
	*ffprobe >> buffer;
	ffprobe->wait();
	ffprobe.reset();

	Json::Value root;
    Json::Reader reader;
    if (reader.parse(buffer, root)) {
		for (Json::Value::const_iterator iter = root["streams"].begin(); iter != root["streams"].end(); iter++) {
			const Json::Value item = *iter;
			Stream stream = parse_stream_info(item);
			std::shared_ptr<Codec::Base> codec;
			if (item["codec_type"] == "video") {
				codec = parse_video_stream_codec(item);
			}
			else if (item["codec_type"] == "audio") {
				codec = parse_audio_stream_codec(item);
			}
			else if (item["codec_type"] == "subtitle") {
				codec = parse_subtitle_stream_codec(item);
			}
			stream.set_codec(codec);
			m_streams.push_back(std::move(stream));
		}
	}
}

Alchemist::Media::Stream Alchemist::Media::File::InFile::parse_stream_info(const Json::Value& item) {
	Stream stream(item["index"].asUInt());
	
	if (item.isMember("tags")) {
		Json::Value tags = item["tags"];
		if (tags.isMember("language"))
			stream.set_language(tags["language"].asString());
	}
	return stream;
}

std::shared_ptr<Alchemist::Media::Codec::Base> Alchemist::Media::File::InFile::parse_video_stream_codec(const Json::Value& item) {
	const std::string codec_name = item["codec_name"].asString(), codec_long_name = item["codec_long_name"].asString();
	std::shared_ptr<Codec::Base> fallback(new Codec::Video::Unknown(codec_name, codec_long_name));
	
	auto codec = std::dynamic_pointer_cast<Codec::Video::Base>(Codec::Instance(codec_name, fallback));
	codec->set_resolution(item["width"].asInt(), item["height"].asInt());

	return codec;
}

std::shared_ptr<Alchemist::Media::Codec::Base> Alchemist::Media::File::InFile::parse_audio_stream_codec(const Json::Value& item) {
	const std::string codec_name = item["codec_name"].asString(), codec_long_name = item["codec_long_name"].asString();
	std::shared_ptr<Codec::Base> fallback(new Codec::Audio::Unknown(codec_name, codec_long_name));

	auto codec = std::dynamic_pointer_cast<Codec::Audio::Base>(Codec::Instance(codec_name, fallback));

	return codec;
}

std::shared_ptr<Alchemist::Media::Codec::Base> Alchemist::Media::File::InFile::parse_subtitle_stream_codec(const Json::Value& item) {
	const std::string codec_name = item["codec_name"].asString(), codec_long_name = item["codec_long_name"].asString();
	std::shared_ptr<Codec::Base> fallback(new Codec::Subtitle::Unknown(codec_name, codec_long_name));
	
	auto codec = std::dynamic_pointer_cast<Codec::Subtitle::Base>(Codec::Instance(codec_name, fallback));

	return codec;
}
