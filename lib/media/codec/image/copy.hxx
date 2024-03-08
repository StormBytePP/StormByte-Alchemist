#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC Copy final: public Base {
		public:
			Copy();
			Copy(const Copy&)					= default;
			Copy(Copy&&)						= default;
			Copy& operator=(const Copy&)		= default;
			Copy& operator=(Copy&&)			= default;
			~Copy()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}