#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC GIF final: public Base {
		public:
			GIF();
			GIF(const GIF&)					= default;
			GIF(GIF&&) noexcept				= default;
			GIF& operator=(const GIF&)		= default;
			GIF& operator=(GIF&&) noexcept	= default;
			~GIF() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}