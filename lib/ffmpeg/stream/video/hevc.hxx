#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Video {
	class HEVC: public Base {
		public:
			class HDR {
				public:
					HDR(unsigned int red_x,				unsigned int red_y,
						unsigned int green_x,			unsigned int green_y,
						unsigned int blue_x,			unsigned int blue_y,
						unsigned int white_point_x,		unsigned int white_point_y,
						unsigned int luminance_min,		unsigned int luminance_max);
					HDR(unsigned int red_x,				unsigned int red_y,
						unsigned int green_x,			unsigned int green_y,
						unsigned int blue_x,			unsigned int blue_y,
						unsigned int white_point_x,		unsigned int white_point_y,
						unsigned int luminance_min,		unsigned int luminance_max,
						unsigned int light_level_max,	unsigned int light_level_average);
					HDR(const HDR& hdr);
					HDR(HDR&&) = default;
					HDR& operator=(const HDR& hdr);
					~HDR() = default;
					void set_light_level(unsigned int light_level_max, unsigned int light_level_average);
					std::string ffmpeg_parameters() const;
			
				private:
					void copy(const HDR& hdr);
					std::pair<std::string, std::string> m_red, m_green, m_blue, m_white_point, m_luminance;
					std::optional<std::pair<std::string, std::string>> m_light_level;
			};

			HEVC(unsigned short stream_id);
			HEVC(const HEVC& hevc);
			HEVC(HEVC&& hevc) = default;
			HEVC& operator=(const HEVC& hevc);
			~HEVC() = default;

			void set_HDR(const HDR& hdr);
			std::list<std::string> ffmpeg_parameters() const;
			
			static const HDR DEFAULT_HDR;

		private:
			std::optional<HDR> m_hdr;
			static const std::string DEFAULT_MAX_BITRATE, DEFAULT_BUFFSIZE, X265_PARAMS;
	};
}