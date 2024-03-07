#pragma once

#include "info.hxx"

#include <list>

namespace Alchemist::Media::Decoder {
	enum DLL_PUBLIC Type:unsigned short {
		// Video
		AV1_DEFAULT, AV1_LIBAOM, AV1_CUVID, AV1_DAV1D,
		H264_DEFAULT, H264_CUVID, H264_OPENH264,
		H265_DEFAULT, H265_CUVID,
		MPEG2_DEFAULT, MPEG2_CUVID,
		VP8_DEFAULT, VP8_CUVID, VP8_LIBVPX,
		VP9_DEFAULT, VP9_CUVID, VP9_LIBVPX,
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

	class DLL_LOCAL Base {
		public:
			Base(const Type&);
			Base(Type&&);
			Base(const Base&)				= default;
			Base(Base&&)					= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&)			= default;
			virtual ~Base()					= 0;

			inline Type get_decoder_type() const;

			static const std::list<Type> DLL_PUBLIC Available;
			static const std::list<Info> DLL_PUBLIC All;

		protected:
			Type m_decoder_type;
	};

	const std::list<Type> DLL_PUBLIC Available	= Base::Available;
	const std::list<Info> DLL_PUBLIC All		= Base::All;
}