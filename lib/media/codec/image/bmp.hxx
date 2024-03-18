#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC BMP final: public Base {
		public:
			BMP();
			BMP(const BMP&)					= default;
			BMP(BMP&&) noexcept				= default;
			BMP& operator=(const BMP&)		= default;
			BMP& operator=(BMP&&) noexcept	= default;
			~BMP() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}