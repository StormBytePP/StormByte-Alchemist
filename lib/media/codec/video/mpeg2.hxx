#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Codec::Video {
	class DLL_PUBLIC MPEG2 final: public Base {
		public:
			MPEG2();
			MPEG2(const MPEG2&)					= default;
			MPEG2(MPEG2&&) noexcept				= default;
			MPEG2& operator=(const MPEG2&)		= default;
			MPEG2& operator=(MPEG2&&) noexcept	= default;
			~MPEG2() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}