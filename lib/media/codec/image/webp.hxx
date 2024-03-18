#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC WEBP final: public Base {
		public:
			WEBP();
			WEBP(const WEBP&)					= default;
			WEBP(WEBP&&) noexcept				= default;
			WEBP& operator=(const WEBP&)		= default;
			WEBP& operator=(WEBP&&) noexcept	= default;
			~WEBP() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}