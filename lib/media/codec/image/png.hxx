#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC PNG final: public Base {
		public:
			PNG();
			PNG(const PNG&)					= default;
			PNG(PNG&&) noexcept				= default;
			PNG& operator=(const PNG&)		= default;
			PNG& operator=(PNG&&) noexcept	= default;
			~PNG() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}