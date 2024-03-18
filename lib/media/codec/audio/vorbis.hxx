#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC VORBIS final: public Base {
		public:
			VORBIS();
			VORBIS(const VORBIS&)					= default;
			VORBIS(VORBIS&&) noexcept				= default;
			VORBIS& operator=(const VORBIS&)		= default;
			VORBIS& operator=(VORBIS&&) noexcept	= default;
			~VORBIS() noexcept						= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}