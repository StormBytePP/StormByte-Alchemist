#include "file.hxx"
#include "../system/executable/ffmpeg.hxx"
#include "../system/executable/ffprobe.hxx"
#include "../system/executable/hdr10plus.hxx"

#include <json/json.h>
#include <stdexcept>

Alchemist::Media::File::File(const std::filesystem::path& file_path):m_media_path(file_path) { }

Alchemist::Media::File::File(std::filesystem::path&& file_path):m_media_path(std::move(file_path)) { }

Alchemist::Media::File Alchemist::Media::File::read(const std::filesystem::path& path) {
	return File(path).check_features();
}

Alchemist::Media::File Alchemist::Media::File::read(std::filesystem::path&& path) {
	return File(std::move(path)).check_features();
}

bool Alchemist::Media::File::has_feature(const Feature& feature) const {
	return (m_features & feature) == feature;
}

Alchemist::Media::File& Alchemist::Media::File::check_features() {
	if (!std::filesystem::is_regular_file(m_media_path))
		throw std::runtime_error("File " + m_media_path.string() + " is not a file but a path");
	else if (!std::filesystem::exists(m_media_path))
		throw std::runtime_error("File " + m_media_path.string() + " do not exist");

	std::unique_ptr<System::FFprobe> ffprobe;
	std::unique_ptr<System::FFmpeg> ffmpeg;
	std::unique_ptr<System::HDR10Plus> hdr10plus_tool;
	std::string buffer;
	m_features = 0;

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

	return *this;
}