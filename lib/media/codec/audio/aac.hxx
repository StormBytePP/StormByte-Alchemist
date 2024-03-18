#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC AAC final: public Base {
		public:
			AAC();
			AAC(const AAC&)					= default;
			AAC(AAC&&) noexcept				= default;
			AAC& operator=(const AAC&)		= default;
			AAC& operator=(AAC&&) noexcept	= default;
			~AAC() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}