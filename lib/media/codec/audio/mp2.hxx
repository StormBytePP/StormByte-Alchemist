#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC MP2 final: public Base {
		public:
			MP2();
			MP2(const MP2&)					= default;
			MP2(MP2&&) noexcept				= default;
			MP2& operator=(const MP2&)		= default;
			MP2& operator=(MP2&&) noexcept	= default;
			~MP2() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}