#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Video {
	class HEVC: public Base {
		public:
			class HDR {
				public:
					HDR(unsigned int red_x,					unsigned int red_y,
						unsigned int green_x,				unsigned int green_y,
						unsigned int blue_x,				unsigned int blue_y,
						unsigned int white_point_x,			unsigned int white_point_y,
						unsigned int luminance_min,			unsigned int luminance_max);
					HDR(unsigned int red_x,					unsigned int red_y,
						unsigned int green_x,				unsigned int green_y,
						unsigned int blue_x,				unsigned int blue_y,
						unsigned int white_point_x,			unsigned int white_point_y,
						unsigned int luminance_min,			unsigned int luminance_max,
						unsigned int light_level_content,	unsigned int light_level_average);
					HDR(const HDR& hdr) = default;
					HDR(HDR&&) noexcept = default;
					HDR& operator=(const HDR& hdr) = default;
					HDR& operator=(HDR&& hdr) noexcept = default;
					~HDR() = default;
					void set_light_level(unsigned int light_level_content, unsigned int light_level_average);
					std::string ffmpeg_parameters() const;

					static const unsigned int DEFAULT_REDX, DEFAULT_REDY, DEFAULT_GREENX, DEFAULT_GREENY, DEFAULT_BLUEX, DEFAULT_BLUEY, DEFAULT_WHITEPOINTX, DEFAULT_WHITEPOINTY, DEFAULT_LUMINANCEMIN, DEFAULT_LUMINANCEMAX;
			
				private:
					std::pair<std::string, std::string> m_red, m_green, m_blue, m_white_point, m_luminance;
					std::optional<std::pair<std::string, std::string>> m_light_level;
			};

			HEVC(unsigned short stream_id);
			HEVC(const HEVC& hevc) = default;
			HEVC(HEVC&& hevc) noexcept = default;
			HEVC& operator=(const HEVC& hevc) = default;
			HEVC& operator=(HEVC&& hevc) noexcept = default;
			~HEVC() = default;

			void set_HDR(const HDR& hdr);
			std::list<std::string> ffmpeg_parameters() const override;
			
			static const HDR DEFAULT_HDR;

		private:
			std::optional<HDR> m_hdr;
			static const std::string DEFAULT_MAX_BITRATE, DEFAULT_BUFFSIZE, X265_PARAMS;

			HEVC* copy() const override;
	};
}