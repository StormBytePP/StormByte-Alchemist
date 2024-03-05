#pragma once

#include "visibility.hxx"

#include <list>

namespace StormByte::VideoConvert::Media {
	struct DLL_PUBLIC Encoders {
		enum Type:unsigned short {
			// Video
			AV1_AOM, AV1_RAV1E, AV1_SVT, AV1_NVENC,
			H264_X264, H264_OPENH264, H264_NVENC,
			H265_X265, H265_NVENC,
			MPEG2_VIDEO,
			VP8_LIBVPX,
			VP9_LIBVPX,
			MPEG4_LIBXVID,

			// Audio
			AAC_DEFAULT, AAC_FRAUNHOFFER,
			AC3_DEFAULT,
			DTS_DEFAULT,
			EAC3_DEFAULT,
			FLAC_DEFAULT,
			MP2_DEFAULT, MP2_TWOLAME,
			MP3_LAME,
			OPUS_DEFAULT, OPUS_LIBOPUS,
			VORBIS_DEFAULT, VORBIS_LIBVORBIS,

			// Image
			BMP_DEFAULT,
			GIF_DEFAULT,
			JPG_DEFAULT,
			PNG_DEFAULT,
			TIFF_DEFAULT,
			WEBP_LIBWEBP
		};

		static const std::list<Type> Available;
	};
}