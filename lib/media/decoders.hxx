#pragma once

#include "visibility.hxx"

#include <list>

namespace StormByte::VideoConvert::Media {
	struct DLL_PUBLIC Decoders {
		enum Type:unsigned short {
			// Video
			AV1_DEFAULT, AV1_DAV1D, AV1_AOM, AV1_CUVID,
			H264_DEFAULT, H264_OPENH264, H264_CUVID,
			H265_DEFAULT, H265_CUVID,
			MPEG2_DEFAULT, MPEG2_CUVID,
			VP8_DEFAULT, VP8_LIBVPX, VP8_CUVID,
			VP9_DEFAULT, VP9_LIBVPX, VP9_CUVID,
			MPEG4_DEFAULT, MPEG4_CUVID,

			// Audio
			AAC_DEFAULT, AAC_FRAUNHOFFER,
			AC3_DEFAULT,
			DTS_DEFAULT,
			EAC3_DEFAULT,
			FLAC_DEFAULT,
			MP2_DEFAULT,
			MP3_DEFAULT,
			OPUS_DEFAULT, OPUS_LIBOPUS,
			VORBIS_DEFAULT, VORBIS_LIBVORBIS,

			// Image
			BMP_DEFAULT,
			GIF_DEFAULT,
			JPG_DEFAULT,
			PNG_DEFAULT,
			TIFF_DEFAULT,
			WEBP_DEFAULT
		};

		static const std::list<Type> Available;
	};
}