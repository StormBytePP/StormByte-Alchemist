#pragma once

#include "visibility.h"

#include <limits>
#include <list>

namespace StormByte::Alchemist::Media::Codec {
	enum DLL_PUBLIC Type:unsigned short {
		AV1, H264, HEVC, MPEG2, VP8, VP9, MPEG4,			// Video
		AAC, AC3, DTS, EAC3, FLAC, MP2, MP3, OPUS, VORBIS,	// Audio
		BMP, GIF, JPG, PNG, TIFF, WEBP,						// Image
		UNKNOWN = std::numeric_limits<unsigned short>::max()
	};

	[[maybe_unused]] static const std::list<Type> DLL_PUBLIC Available();
}