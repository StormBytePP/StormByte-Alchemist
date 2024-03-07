#pragma once

#include "decoder.hxx"
#include "encoder.hxx"

#include <limits>
#include <list>

namespace Alchemist::Media::Codec {
	enum DLL_PUBLIC Type:unsigned short {
		AV1, H264, H265, MPEG2, VP8, VP9, MPEG4,			// Video
		AAC, AC3, DTS, EAC3, FLAC, MP2, MP3, OPUS, VORBIS,	// Audio
		BMP, GIF, JPG, PNG, TIFF, WEBP,						// Image
		UNKNOWN = std::numeric_limits<unsigned short>::max()
	};

	class DLL_PUBLIC Base {
		public:
			Base(const Type&);
			Base(Type&&);
			Base(const Base&)												= default;
			Base(Base&&)													= default;
			Base& operator=(const Base&)									= default;
			Base& operator=(Base&&)											= default;
			virtual ~Base()													= default;

			virtual bool is_video() const									= 0;
			virtual bool is_audio() const									= 0;
			virtual bool is_image() const									= 0;

			inline  Type get_codec_type() const;
			virtual std::list<Decoder::Type> get_available_decoders() const	= 0;
			virtual std::list<Encoder::Type> get_available_encoders() const	= 0;

			static const std::list<Type> DLL_PUBLIC Available;
			static const std::list<Info> DLL_PUBLIC All;

		protected:
			 Type m_codec_type;
	};

	const std::list<Type> DLL_PUBLIC Available	= Base::Available;
	const std::list<Info> DLL_PUBLIC All		= Base::All;
}