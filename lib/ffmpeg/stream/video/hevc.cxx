#include "hevc.hxx"

using namespace StormByte::VideoConvert;

/******************************* HDR ************************************/
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_REDX			= 34000;
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_REDY			= 16000;
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_GREENX		= 13250;
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_GREENY		= 34500;
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_BLUEX			= 7500;
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_BLUEY			= 3000;
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTX	= 15635;
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTY	= 16450;
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMIN	= 1;
const unsigned int Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMAX	= 10000000;

Stream::Video::HEVC::HDR::HDR(	unsigned int red_x, unsigned int red_y,
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

Stream::Video::HEVC::HDR::HDR(	unsigned int red_x,				unsigned int red_y,
														unsigned int green_x,			unsigned int green_y,
														unsigned int blue_x,			unsigned int blue_y,
														unsigned int white_point_x,		unsigned int white_point_y,
														unsigned int luminance_min,		unsigned int luminance_max,
														unsigned int light_level_max,	unsigned int light_level_average) {

	m_red 			= std::make_pair(std::to_string(red_x),			std::to_string(red_y));
	m_green 		= std::make_pair(std::to_string(green_x),		std::to_string(green_y));
	m_blue			= std::make_pair(std::to_string(blue_x),		std::to_string(blue_y));
	m_white_point 	= std::make_pair(std::to_string(white_point_x),	std::to_string(white_point_y));
	m_luminance 	= std::make_pair(std::to_string(luminance_min),	std::to_string(luminance_max));
	m_light_level 	= std::make_pair(std::to_string(light_level_max), std::to_string(light_level_average));
}

void Stream::Video::HEVC::HDR::set_light_level(unsigned int light_level_max, unsigned int light_level_average) {
	m_light_level = std::make_pair(std::to_string(light_level_max), std::to_string(light_level_average));
}

std::string Stream::Video::HEVC::HDR::ffmpeg_parameters() const {
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

	if (m_light_level)
		result += ":max-cll=" + m_light_level->first + "," + m_light_level->second;

	result += ":hdr10=1";

	return result;
}





/********************************* HEVC *************************************/
const std::string Stream::Video::HEVC::DEFAULT_MAX_BITRATE 	= "6M";
const std::string Stream::Video::HEVC::DEFAULT_BUFFSIZE 	= "200M";
const std::string Stream::Video::HEVC::X265_PARAMS 			= "level=5.1:aq-mode=3:colorprim=bt2020:colormatrix=bt2020nc";
const Stream::Video::HEVC::HDR Stream::Video::HEVC::DEFAULT_HDR = HDR(HDR::DEFAULT_REDX, HDR::DEFAULT_REDY, HDR::DEFAULT_GREENX, HDR::DEFAULT_GREENY, HDR::DEFAULT_BLUEX, HDR::DEFAULT_BLUEY, HDR::DEFAULT_WHITEPOINTX, HDR::DEFAULT_WHITEPOINTY, HDR::DEFAULT_LUMINANCEMIN, HDR::DEFAULT_LUMINANCEMIN);

Stream::Video::HEVC::HEVC(unsigned short stream_id):Stream::Video::Base(stream_id, "libx265", Database::Data::VIDEO_HEVC) {
	m_max_rate = DEFAULT_MAX_BITRATE;
}

Stream::Video::HEVC* Stream::Video::HEVC::copy() const {
	return new HEVC(*this);
}

void Stream::Video::HEVC::set_HDR(const HDR& hdr) {
	m_hdr = hdr;
}

std::list<std::string> Stream::Video::HEVC::ffmpeg_parameters() const {
	std::list<std::string> result = Stream::Video::Base::ffmpeg_parameters();
	std::string x265_params;
	if (m_hdr)
		x265_params = (X265_PARAMS + ":" + m_hdr->ffmpeg_parameters() + ":transfer=smpte2084"); //Transfer only works with HDR it seems
	else
		x265_params = X265_PARAMS;

	result.push_back("-profile:" + ffmpeg_stream_id());					result.push_back("main10");
	result.push_back("-level:" + ffmpeg_stream_id());					result.push_back("5.1");
	result.push_back("-x265-params:" + ffmpeg_stream_id());				result.push_back(x265_params);
	result.push_back("-pix_fmt:" + ffmpeg_stream_id());					result.push_back("yuv420p10le");
	result.push_back("-bufsize:" + ffmpeg_stream_id());					result.push_back(DEFAULT_BUFFSIZE);
	if (m_is_animation) {
		result.push_back("-tune:" + ffmpeg_stream_id());				result.push_back("animation");
	}

	return result;
}
