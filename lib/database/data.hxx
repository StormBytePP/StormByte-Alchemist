#pragma once

#include <optional>
#include <filesystem>
#include <map>
#include <list>

namespace StormByte::VideoConvert::Database::Data {
	struct film {
		enum priority: unsigned short {
			LOW 		= 0,
			NORMAL,
			HIGH,
			IMPORTANT,
			MAX
		};

		struct group {
			unsigned int id;
			std::filesystem::path folder;
		};

		struct stream {
			/* Since these define their values on database they will all be defined even if not enabled */
			enum codec: unsigned short {
				VIDEO_HEVC = 0,
				VIDEO_COPY,
				AUDIO_AAC,
				AUDIO_FDKAAC,
				AUDIO_AC3,
				AUDIO_COPY,
				AUDIO_EAC3,
				AUDIO_OPUS,
				SUBTITLE_COPY,
				INVALID_CODEC = 666
			};

			inline static const std::map<codec, std::string> codec_string {
				{ VIDEO_HEVC, 		"HEVC/H.265" },
				{ VIDEO_COPY, 		"Video Copy" },
				{ AUDIO_AAC, 		"Advanced Audio Codec (AAC)" },
				{ AUDIO_FDKAAC, 	"Fraunhoffer Advanced Audio Codec (AAC-HE)" },
				{ AUDIO_AC3, 		"Dolby AC-3" },
				{ AUDIO_COPY,		"Audio Copy" },
				{ AUDIO_EAC3, 		"Dolby Enhanced AC-3" },
				{ AUDIO_OPUS,		"Opus" },
				{ SUBTITLE_COPY,	"Subtitle Copy" },
				{ INVALID_CODEC,	"Invalid or unsupported codec"}
			};

			struct hdr {
				unsigned int red_x;
				unsigned int red_y;
				unsigned int green_x;
				unsigned int green_y;
				unsigned int blue_x;
				unsigned int blue_y;
				unsigned int white_point_x;
				unsigned int white_point_y;
				unsigned int luminance_min;
				unsigned int luminance_max;
				std::optional<std::pair<unsigned int, unsigned int>> light_level;
			};


			short m_id = 0; // Negative value means all
			codec m_codec;
			bool m_is_animation = false;
			std::optional<std::string> m_max_rate, m_bitrate;
			std::optional<hdr> m_hdr;
		};

		std::optional<unsigned int> m_id; //No value means not in database or not queried
		std::filesystem::path m_file;
		priority m_priority = NORMAL;
		std::optional<std::filesystem::path> m_title;
		bool m_processing = false;
		bool m_unsupported = false;
		std::optional<group> m_group;
		std::list<stream> m_streams;
	};
}
