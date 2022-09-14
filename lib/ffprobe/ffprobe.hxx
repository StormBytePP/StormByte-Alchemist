#pragma once

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

			struct stream {
				enum TYPE: char { VIDEO = 'v', AUDIO = 'a', SUBTITLE = 's' };

				std::string codec_name;
				std::optional<std::string> language;
			};

			/* Initialize */
			void initialize_video_data(const std::string& json);
			void initialize_stream_data(const std::string& json, const stream::TYPE& type);

			/* Getters */
			std::optional<std::string> get_pix_fmt() const { return m_pix_fmt; }
			std::optional<std::string> get_color_space() const { return m_color_space; }
			std::optional<std::string> get_color_primaries() const { return m_color_primaries; }
			std::optional<std::string> get_color_transfer() const { return m_color_transfer; }


			#ifdef ENABLE_HEVC
			bool is_HDR_detected() const;
			bool is_HDR_factible() const; // When HDR metadata is missing but color space is compatible
			#endif

		private:
			std::optional<Json::Value> parse_json(const std::string& json) const;
			
			std::optional<std::string> m_pix_fmt, m_color_space, m_color_primaries, m_color_transfer;
			/* HDR */
			#ifdef ENABLE_HEVC
			std::optional<std::string> m_red_x, m_red_y, m_green_x, m_green_y, m_blue_x, m_blue_y, m_white_point_x, m_white_point_y, m_min_luminance, m_max_luminance, m_max_content, m_max_average;
			#endif
			std::map<stream::TYPE, std::vector<stream>> m_streams;
	};
}
