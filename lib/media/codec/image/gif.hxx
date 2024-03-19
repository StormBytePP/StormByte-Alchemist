#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC GIF final: public Base {
		public:
			GIF();

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}