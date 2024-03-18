#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC Copy final: public Base {
		public:
			Copy();
			Copy(const Copy&)				= default;
			Copy(Copy&&) noexcept			= default;
			Copy& operator=(const Copy&)	= default;
			Copy& operator=(Copy&&) noexcept= default;
			~Copy() noexcept				= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}