#include "hevc.hxx"

/******************************* HDR ************************************/
StormByte::VideoConvert::Stream::Video::HEVC::HDR::HDR(	unsigned int red_x, unsigned int red_y,
														unsigned int green_x,			unsigned int green_y,
														unsigned int blue_x,			unsigned int blue_y,
														unsigned int white_point_x,		unsigned int white_point_y,
														unsigned int luminance_min,		unsigned int luminance_max) {

	m_red 			= std::make_pair(std::to_string(red_x),			std::to_string(red_y));
	m_green 		= std::make_pair(std::to_string(green_x),		std::to_string(green_y));
	m_blue			= std::make_pair(std::to_string(blue_x),		std::to_string(blue_y));
	m_white_point 	= std::make_pair(std::to_string(white_point_x),	std::to_string(white_point_y));
	m_luminance 	= std::make_pair(std::to_string(luminance_min),	std::to_string(luminance_max));
}

StormByte::VideoConvert::Stream::Video::HEVC::HDR::HDR(	unsigned int red_x,				unsigned int red_y,
														unsigned int green_x,			unsigned int green_y,
														unsigned int blue_x,			unsigned int blue_y,
														unsigned int white_point_x,		unsigned int white_point_y,
														unsigned int luminance_min,		unsigned int luminance_max,
														unsigned int light_level_max,	unsigned int light_level_average) {

	HDR(red_x, red_y, green_x, green_y, blue_x, blue_y, white_point_x, white_point_y, luminance_min, luminance_max);
	m_light_level = std::make_pair(std::to_string(light_level_max), std::to_string(light_level_average));
}

StormByte::VideoConvert::Stream::Video::HEVC::HDR::HDR(const HDR& hdr) {
	copy(hdr);
}

StormByte::VideoConvert::Stream::Video::HEVC::HDR& StormByte::VideoConvert::Stream::Video::HEVC::HDR::operator=(const HDR& hdr) {
	if (&hdr != this) {
		copy(hdr);
	}
	return *this;
}

void StormByte::VideoConvert::Stream::Video::HEVC::HDR::set_light_level(unsigned int light_level_max, unsigned int light_level_average) {
	m_light_level = std::make_pair(std::to_string(light_level_max), std::to_string(light_level_average));
}

void StormByte::VideoConvert::Stream::Video::HEVC::HDR::copy(const HDR& hdr) {
	m_red 			= hdr.m_red;
	m_green			= hdr.m_green;
	m_blue			= hdr.m_blue;
	m_white_point	= hdr.m_white_point;
	m_luminance		= hdr.m_luminance;
}

std::string StormByte::VideoConvert::Stream::Video::HEVC::HDR::ffmpeg_parameters() const {
	/* Warning:
		* There is an specific order for master-display which is G()B()R()WP()L()
		* Wrong order will cause libx265 to ignore HDR and not handling it!
	*/

	std::string result = "master-display=";
	result += "G(" + m_green.first + "," + m_green.second + ")";
	result += "B(" + m_blue.first + "," + m_blue.second + ")";
	result += "R(" + m_red.first + "," + m_red.second + ")";
	result += "WP(" + m_white_point.first + "," + m_white_point.second + ")";
	result += "L(" + m_luminance.second + "," + m_luminance.first + ")";

	if (m_light_level.has_value())
		result += ":max-cll=" + m_light_level->first + "," + m_light_level->second;

	result += ":hdr10=1";

	return result;
}





/********************************* HEVC *************************************/
const std::string StormByte::VideoConvert::Stream::Video::HEVC::DEFAULT_MAX_BITRATE 	= "6M";
const std::string StormByte::VideoConvert::Stream::Video::HEVC::DEFAULT_BUFFSIZE 	= "200M";
const std::string StormByte::VideoConvert::Stream::Video::HEVC::X265_PARAMS 			= "level=5.1:aq-mode=3:colorprim=bt2020:transfer=smpte2084:colormatrix=bt2020nc";
const StormByte::VideoConvert::Stream::Video::HEVC::HDR StormByte::VideoConvert::Stream::Video::HEVC::DEFAULT_HDR = HDR(34000, 16000, 13250, 34500, 7500, 3000, 15635, 16450, 1, 10000000);

StormByte::VideoConvert::Stream::Video::HEVC::HEVC(unsigned short stream_id):StormByte::VideoConvert::Stream::Video::Base(stream_id, "libx265") {
	m_max_rate = DEFAULT_MAX_BITRATE;
}

StormByte::VideoConvert::Stream::Video::HEVC::HEVC(const HEVC& hevc):StormByte::VideoConvert::Stream::Video::Base(hevc) {
	m_hdr = hevc.m_hdr;
	m_bitrate = hevc.m_bitrate;
}

StormByte::VideoConvert::Stream::Video::HEVC& StormByte::VideoConvert::Stream::Video::HEVC::operator=(const HEVC& hevc) {
	if (&hevc != this) {
		StormByte::VideoConvert::Stream::Video::Base::operator=(hevc);
		m_hdr = hevc.m_hdr;
	}
	return *this;
}

void StormByte::VideoConvert::Stream::Video::HEVC::set_HDR(const HDR& hdr) {
	m_hdr = hdr;
}

std::list<std::string> StormByte::VideoConvert::Stream::Video::HEVC::ffmpeg_parameters() const {
	std::list<std::string> result = StormByte::VideoConvert::Stream::Video::Base::ffmpeg_parameters();
	std::string x265_params;
	if (m_hdr.has_value())
		x265_params = ("\"" + X265_PARAMS + ":" + m_hdr.value().ffmpeg_parameters() + "\"");
	else
		x265_params = ("\"" + X265_PARAMS + "\"");

	result.push_back("-profile:v:" + std::to_string(m_stream_id));		result.push_back("main10");
	result.push_back("-level:v:" + std::to_string(m_stream_id));		result.push_back("5.1");
	result.push_back("-x265-params:v:" + std::to_string(m_stream_id));	result.push_back(x265_params);
	result.push_back("-pix_fmt:v:" + std::to_string(m_stream_id));		result.push_back("yuv420p10le");
	result.push_back("-bufsize:v:" + std::to_string(m_stream_id));		result.push_back(DEFAULT_BUFFSIZE);
	if (m_is_animation) {
		result.push_back("-tune:v:" + std::to_string(m_stream_id));		result.push_back("animation");
	}

	return result;
}
