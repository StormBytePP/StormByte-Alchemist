#pragma once

#include "item.hxx"
#include "decoder.hxx"
#include "encoder.hxx"

#include <list>
#include <memory>
#include <optional>
#include <string>

namespace Alchemist::Media::Codec {
	enum DLL_PUBLIC Type:unsigned short {
		AV1, H264, H265, MPEG2, VP8, VP9, MPEG4,			// Video
		AAC, AC3, DTS, EAC3, FLAC, MP2, MP3, OPUS, VORBIS,	// Audio
		BMP, GIF, JPG, PNG, TIFF, WEBP,						// Image
		
		// Special Items
		COPY_VIDEO		= std::numeric_limits<unsigned short>::max() - 7,
		COPY_AUDIO		= std::numeric_limits<unsigned short>::max() - 6,
		COPY_IMAGE		= std::numeric_limits<unsigned short>::max() - 5,
		COPY_SUBTITLE	= std::numeric_limits<unsigned short>::max() - 4,

		UNKNOWN_VIDEO	= std::numeric_limits<unsigned short>::max() - 3,
		UNKNOWN_AUDIO	= std::numeric_limits<unsigned short>::max() - 2,
		UNKNOWN_IMAGE	= std::numeric_limits<unsigned short>::max() - 1,
		UNKNOWN_SUBTITLE= std::numeric_limits<unsigned short>::max()
	};

	class DLL_PUBLIC Base: public Item {
		public:
			Base(const Type&);
			Base(Type&&);
			virtual ~Base()	noexcept											= default;

			virtual bool is_video() 	const noexcept							= 0;
			virtual bool is_audio() 	const noexcept							= 0;
			virtual bool is_image() 	const noexcept							= 0;
			virtual bool is_subtitle()	const noexcept							= 0;

			Type get_codec_type() const noexcept;
			virtual std::string get_name() const;
			virtual std::string get_long_name() const;
			const std::optional<std::string>& get_language() const noexcept;
			void set_language(const std::string&);
			void set_language(std::string&&) noexcept;
			virtual std::list<Decoder::Type> get_available_decoders() const	= 0;
			virtual std::list<Encoder::Type> get_available_encoders() const	= 0;

		protected:
			Type m_codec_type;
			std::optional<std::string> m_language;
	};

	std::shared_ptr<Base> DLL_PUBLIC Instance(const Type&);
	std::shared_ptr<Base> DLL_PUBLIC Instance(const std::string&, std::shared_ptr<Base>);
}