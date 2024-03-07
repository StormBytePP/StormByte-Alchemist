#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Codec::Video {
	class DLL_PUBLIC H264 final: public Base {
		public:
			H264();
			H264(const H264&)					= default;
			H264(H264&&)						= default;
			H264& operator=(const H264&)		= default;
			H264& operator=(H264&&)			= default;
			~H264()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}