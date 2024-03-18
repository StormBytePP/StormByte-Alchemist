#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC FLAC final: public Base {
		public:
			FLAC();
			FLAC(const FLAC&)					= default;
			FLAC(FLAC&&) noexcept				= default;
			FLAC& operator=(const FLAC&)		= default;
			FLAC& operator=(FLAC&&) noexcept	= default;
			~FLAC() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}