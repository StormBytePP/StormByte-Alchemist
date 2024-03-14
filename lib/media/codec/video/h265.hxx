#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Codec::Video {
	class DLL_PUBLIC H265 final: public Base {
		public:
			H265();
			H265(const H265&)				= default;
			H265(H265&&)					= default;
			H265& operator=(const H265&)	= default;
			H265& operator=(H265&&)			= default;
			~H265()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}