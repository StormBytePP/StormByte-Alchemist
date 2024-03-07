#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC AC3 final: public Base {
		public:
			AC3();
			AC3(const AC3&)					= default;
			AC3(AC3&&)						= default;
			AC3& operator=(const AC3&)		= default;
			AC3& operator=(AC3&&)			= default;
			~AC3()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}