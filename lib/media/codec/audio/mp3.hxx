#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC MP3 final: public Base {
		public:
			MP3();
			MP3(const MP3&)					= default;
			MP3(MP3&&) noexcept				= default;
			MP3& operator=(const MP3&)		= default;
			MP3& operator=(MP3&&) noexcept	= default;
			~MP3() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}