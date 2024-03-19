#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC EAC3 final: public Base {
		public:
			EAC3();

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}