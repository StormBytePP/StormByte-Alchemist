#pragma once

#include "visibility.hxx"

#include <list>
#include <map>
#include <utility>
#include <string>
#include <limits>

namespace StormByte::VideoConvert::Media {
	struct DLL_PUBLIC Encoders {
		enum Encoder:unsigned short {
			AV1, H264, H265, MPEG2, RAV1E, VP8, VP9, XVID,			// Video
			AAC, AC3, DTS, EAC3, FDK_AAC, FLAC, MP3, OPUS, VORBIS,	// Audio
			BMP, GIF, JPG, PNG, TIFF, WEBP,								// Image
			UNKNOWN = std::numeric_limits<unsigned short>::max()
		};
		static const std::list<Encoder> Available;
		static const std::map<Encoder, std::pair<std::string, std::string>> Names;

		bool is_video(const Encoder&) const;
		bool is_audio(const Encoder&) const;
		bool is_image(const Encoder&) const;
	};
}