#pragma once

#include "decoder.hxx"
#include "encoder.hxx"

#include <list>
#include <memory>
#include <optional>

namespace Alchemist::Media::Codec {
	enum DLL_PUBLIC Type:unsigned short {
		AV1, H264, H265, MPEG2, VP8, VP9, MPEG4,			// Video
		AAC, AC3, DTS, EAC3, FLAC, MP2, MP3, OPUS, VORBIS,	// Audio
		BMP, GIF, JPG, PNG, TIFF, WEBP,						// Image
		// Copy special items
		COPY_VIDEO	= std::numeric_limits<unsigned short>::max() - 2,
		COPY_AUDIO	= std::numeric_limits<unsigned short>::max() - 1,
		COPY_IMAGE	= std::numeric_limits<unsigned short>::max()
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

			Type get_codec_type() const;
			const std::optional<std::string>& get_language() const;
			void set_language(const std::string&);
			void set_language(std::string&&);
			virtual std::list<Decoder::Type> get_available_decoders() const	= 0;
			virtual std::list<Encoder::Type> get_available_encoders() const	= 0;

		protected:
			Type m_codec_type;
			std::optional<std::string> m_language;
	};

	std::shared_ptr<Base> DLL_PUBLIC Instance(const Type&);
}