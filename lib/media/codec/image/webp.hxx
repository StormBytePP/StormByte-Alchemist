#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC WEBP final: public Base {
		public:
			WEBP();
			WEBP(const WEBP&)					= default;
			WEBP(WEBP&&)						= default;
			WEBP& operator=(const WEBP&)		= default;
			WEBP& operator=(WEBP&&)				= default;
			~WEBP()								= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}