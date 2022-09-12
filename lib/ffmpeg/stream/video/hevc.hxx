#pragma once

#include "base.hxx"
#include "database/data.hxx"

namespace StormByte::VideoConvert::Stream::Video {
	class HEVC: public Base {
		public:
			class HDR {
				public:
					HDR(const unsigned int& red_x,					const unsigned int& red_y,
						const unsigned int& green_x,				const unsigned int& green_y,
						const unsigned int& blue_x,					const unsigned int& blue_y,
						const unsigned int& white_point_x,			const unsigned int& white_point_y,
						const unsigned int& luminance_min,			const unsigned int& luminance_max);
					HDR(const unsigned int& red_x,					const unsigned int& red_y,
						const unsigned int& green_x,				const unsigned int& green_y,
						const unsigned int& blue_x,					const unsigned int& blue_y,
						const unsigned int& white_point_x,			const unsigned int& white_point_y,
						const unsigned int& luminance_min,			const unsigned int& luminance_max,
						const unsigned int& light_level_content,	const unsigned int& light_level_average);
					HDR(const HDR& hdr) = default;
					HDR(HDR&&) noexcept = default;
					inline HDR(const Database::Data::hdr& hdr) { m_data = hdr; }
					inline HDR(Database::Data::hdr&& hdr) noexcept { m_data = std::move(hdr); }
					HDR& operator=(const HDR& hdr) = default;
					HDR& operator=(HDR&& hdr) noexcept = default;
					inline HDR& operator=(const Database::Data::hdr& hdr) { m_data = hdr; return *this; }
					inline HDR& operator=(Database::Data::hdr&& hdr) { m_data = std::move(hdr); return *this; }
					~HDR() = default;
					inline void set_light_level(const unsigned int& light_level_content, const unsigned int& light_level_average) { m_data.light_level = std::make_pair(light_level_content, light_level_average); }
					std::string ffmpeg_parameters() const;

					static const unsigned int DEFAULT_REDX, DEFAULT_REDY, DEFAULT_GREENX, DEFAULT_GREENY, DEFAULT_BLUEX, DEFAULT_BLUEY, DEFAULT_WHITEPOINTX, DEFAULT_WHITEPOINTY, DEFAULT_LUMINANCEMIN, DEFAULT_LUMINANCEMAX;
			
				private:
					Database::Data::hdr m_data;
			};

			HEVC(const unsigned short& stream_id);
			HEVC(unsigned short&& stream_id);
			HEVC(const HEVC& hevc) = default;
			HEVC(HEVC&& hevc) noexcept = default;
			HEVC& operator=(const HEVC& hevc) = default;
			HEVC& operator=(HEVC&& hevc) noexcept = default;
			~HEVC() = default;

			inline void set_HDR(const HDR& hdr) { m_hdr = hdr; }
			inline void set_HDR(HDR&& hdr) { m_hdr = std::move(hdr); }
			inline void set_HDR(const Database::Data::hdr& hdr) { m_hdr = hdr; }
			inline void set_HDR(Database::Data::hdr&& hdr) { m_hdr = std::move(hdr); }
			std::list<std::string> ffmpeg_parameters() const override;
			
			static const HDR DEFAULT_HDR;

		private:
			std::optional<HDR> m_hdr;
			static const std::string DEFAULT_MAX_BITRATE, DEFAULT_BUFFSIZE, X265_PARAMS;

			inline HEVC* copy() const override { return new HEVC(*this); }
	};
}
