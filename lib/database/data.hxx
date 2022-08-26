#pragma once

#include <optional>
#include <filesystem>

namespace StormByte::VideoConvert::Database::Data {
	struct film {
		std::filesystem::path file = "";
		unsigned short prio = 0;
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

	struct stream {
		unsigned short id = 0;
		int film_id = 0;
		stream_codec codec;
		std::optional<std::string> max_rate;
		std::optional<std::string> bitrate;
		std::optional<hdr> HDR;
	};
}
