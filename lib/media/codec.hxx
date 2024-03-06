#pragma once

#include "media.hxx"

#include <limits>
#include <list>
#include <map>

namespace Alchemist::Media::Codec {
	enum DLL_PUBLIC Type:unsigned short {
		AV1, H264, H265, MPEG2, VP8, VP9, MPEG4,			// Video
		AAC, AC3, DTS, EAC3, FLAC, MP2, MP3, OPUS, VORBIS,	// Audio
		BMP, GIF, JPG, PNG, TIFF, WEBP,						// Image
		UNKNOWN = std::numeric_limits<unsigned short>::max()
	};

	[[maybe_unused]] const std::list<Type> DLL_PUBLIC Available();
	[[maybe_unused]] const std::map<Type, Info> DLL_PUBLIC Metadata();

	class Base {
		public:
			Base(const Codec::Type&);
			Base(Codec::Type&&);
			Base(const Base&)				= default;
			Base(Base&&)					= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&)			= default;
			virtual ~Base()					= default;

			virtual bool is_video() const	= 0;
			virtual bool is_audio() const	= 0;
			virtual bool is_image() const	= 0;

			inline Codec::Type get_codec_type() const;

		protected:
			Codec::Type m_codec_type;
	};
}