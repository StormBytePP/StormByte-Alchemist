#pragma once

#include "info.hxx"

#include <list>

namespace Alchemist::Media {
	struct DLL_PUBLIC Encoder {
		enum Type:unsigned short {
			// Video
			AV1_AOM, AV1_RAV1E, AV1_SVT, AV1_NVENC,
			H264_X264, H264_OPENH264, H264_NVENC,
			H265_X265, H265_NVENC,
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

		[[maybe_unused]] static const std::list<Type> DLL_PUBLIC Available();
		[[maybe_unused]] static const std::list<Info> DLL_PUBLIC All();

		class DLL_PUBLIC Base {
			public:
				Base(const Type&);
				Base(Type&&);
				Base(const Base&)				= default;
				Base(Base&&)					= default;
				Base& operator=(const Base&)	= default;
				Base& operator=(Base&&)			= default;
				virtual ~Base()					= 0;

				inline Type get_decoder_type() const;

			protected:
				Type m_encoder_type;
		};
	};
}