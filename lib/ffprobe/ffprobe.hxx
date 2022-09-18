#pragma once

#include "ffmpeg/stream/video/hevc.hxx"

#include <optional>
#include <string>
#include <map>
#include <jsoncpp/json/json.h>

namespace StormByte::VideoConvert {
	class FFprobe {
		public:
			FFprobe();
			FFprobe(const FFprobe&) = default;
			FFprobe(FFprobe&&) = default;
			FFprobe& operator=(const FFprobe&) = default;
			FFprobe& operator=(FFprobe&&) = default;
			~FFprobe() = default;

			static FFprobe from_file(const Types::path_t&) noexcept;

			struct stream {
				enum TYPE: char { VIDEO = 'v', AUDIO = 'a', SUBTITLE = 's' };
				enum RESOLUTION: unsigned short { RES_480P = 0, RES_720P, RES_1080P, RES_4K, RES_8K };
				static const std::map<RESOLUTION, std::string> RESOLUTION_STRING;
				static const std::map<RESOLUTION, unsigned short> RESOLUTION_MAX_HEIGHT;

				std::string codec_name;
				std::optional<std::string> language;
			};

			/* Initialize */
			void initialize(const Types::path_t&) noexcept;

			/* Getters */
			inline std::optional<std::string>		get_pix_fmt() const { return m_pix_fmt; }
			inline std::optional<std::string>		get_color_space() const { return m_color_space; }
			inline std::optional<std::string>		get_color_primaries() const { return m_color_primaries; }
			inline std::optional<std::string>		get_color_transfer() const { return m_color_transfer; }
			inline const auto&						get_stream(const stream::TYPE& type) const { return m_streams.at(type); }
			inline std::optional<unsigned short>	get_width() const { return m_width; }
			std::optional<stream::RESOLUTION>		get_resolution() const;


			#ifdef ENABLE_HEVC
			bool is_HDR_detected() const;
			bool is_HDR_factible() const; // When HDR metadata is missing but color space is compatible
			Stream::Video::HEVC::HDR get_HDR() const;
			#endif

		private:
			void initialize_video_color_data(const std::string& json);
			void initialize_video_resolution(const std::string& json);
			void initialize_stream_data(const std::string& json, const stream::TYPE& type);
			std::optional<Json::Value> parse_json(const std::string& json) const;
			
			std::optional<std::string> m_pix_fmt, m_color_space, m_color_primaries, m_color_transfer;
			std::optional<unsigned short> m_width, m_height;
			/* HDR */
			#ifdef ENABLE_HEVC
			std::optional<std::string> m_red_x, m_red_y, m_green_x, m_green_y, m_blue_x, m_blue_y, m_white_point_x, m_white_point_y, m_min_luminance, m_max_luminance, m_max_content, m_max_average;
			#endif
			std::map<stream::TYPE, std::vector<stream>> m_streams;
	};
}
