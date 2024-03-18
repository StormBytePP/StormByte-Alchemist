#include "infile.hxx"

#include "base.hxx"
#include "../../system/executable/ffmpeg.hxx"
#include "../../system/executable/ffprobe.hxx"
#include "../../system/executable/hdr10plus.hxx"

#include <json/json.h>

Alchemist::Media::File::InFile::InFile(const std::filesystem::path& file_path):Base(file_path) {
	check();
}

Alchemist::Media::File::InFile::InFile(std::filesystem::path&& file_path):Base(std::move(file_path)) {
	check();
}

bool Alchemist::Media::File::InFile::check() {
	m_features 	= 0;
	m_status 	= 0;

	if (!std::filesystem::exists(m_media_path) || !std::filesystem::is_regular_file(m_media_path)) {
		m_status |= Status::NOT_EXISTS;
		return false;
	}

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
	return true;
}