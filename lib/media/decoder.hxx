#pragma once

#include "item.hxx"

#include <list>
#include <memory>

namespace Alchemist::Media::Decoder {
	enum DLL_PUBLIC Type:unsigned short {
		// Video
		AV1_LIBAOM, AV1_CUVID, AV1_DAV1D,
		H264_CUVID, H264_OPENH264,
		H265_CUVID,
		MPEG2_CUVID,
		VP8_CUVID, VP8_LIBVPX,
		VP9_CUVID, VP9_LIBVPX,
		MPEG4_CUVID,

		// Audio
		AAC_FRAUNHOFFER, OPUS_LIBOPUS, VORBIS_LIBVORBIS,

		// Image
	};

	class DLL_PUBLIC Base: public Item {
		public:
			Base(const Type&);
			Base(Type&&);
			Base(const Base&)				= default;
			Base(Base&&)					= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&)			= default;
			virtual ~Base()					= 0;

			Type get_decoder_type() const;

		protected:
			Type m_decoder_type;
	};

	std::shared_ptr<Base> DLL_PUBLIC Instance(const Type&);
}