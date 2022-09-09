#pragma once

#include <optional>
#include <filesystem>
#include <map>

namespace StormByte::VideoConvert::Database::Data {
	struct film {
		enum priority: unsigned short {
			LOW 		= 0,
			NORMAL,
			HIGH,
			IMPORTANT,
			MAX
		};
		unsigned int film_id;
		std::filesystem::path file = "";
		unsigned short prio = NORMAL;
		bool processing = false;
	};

	struct hdr {
		int red_x;
		int red_y;
		int green_x;
		int green_y;
		int blue_x;
		int blue_y;
		int white_point_x;
		int white_point_y;
		int luminance_min;
		int luminance_max;
		std::optional<int> light_level_max;
		std::optional<int> light_level_average;
	};

	/* Since these define their values on database they will all be defined even if not enabled */
	enum stream_codec: int {
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

	static const std::map<stream_codec, std::string> codec_string {
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

	struct stream {
		unsigned short id = 0;
		int film_id = 0;
		stream_codec codec;
		bool is_animation = false;
		std::optional<std::string> max_rate;
		std::optional<std::string> bitrate;
		std::optional<hdr> HDR;
	};
}
