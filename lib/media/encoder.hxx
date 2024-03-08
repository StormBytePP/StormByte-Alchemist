#pragma once

#include "visibility.h"

#include <list>
#include <memory>

namespace Alchemist::Media::Encoder {
	enum DLL_PUBLIC Type:unsigned short {
		// Video
		AV1_LIBAOM, AV1_NVENC, AV1_RAV1E, AV1_SVT,
		H264_NVENC, H264_OPENH264, H264_X264,
		H265_NVENC, H265_X265,
		MPEG2_DEFAULT,
		VP8_LIBVPX,
		VP9_LIBVPX,
		MPEG4_DEFAULT, MPEG4_LIBXVID,

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

	class DLL_PUBLIC Base {
		public:
			Base(const Type&);
			Base(Type&&);
			Base(const Base&)				= default;
			Base(Base&&)					= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&)			= default;
			virtual ~Base()					= 0;

			Type get_encoder_type() const;

		protected:
			Type m_encoder_type;
	};

	std::shared_ptr<Base> DLL_PUBLIC Instance(const Type&);
}