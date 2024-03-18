#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC OPUS final: public Base {
		public:
			OPUS();
			OPUS(const OPUS&)					= default;
			OPUS(OPUS&&) noexcept				= default;
			OPUS& operator=(const OPUS&)		= default;
			OPUS& operator=(OPUS&&) noexcept	= default;
			~OPUS() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}