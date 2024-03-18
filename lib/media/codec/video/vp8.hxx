#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Codec::Video {
	class DLL_PUBLIC VP8 final: public Base {
		public:
			VP8();
			VP8(const VP8&)					= default;
			VP8(VP8&&) noexcept				= default;
			VP8& operator=(const VP8&)		= default;
			VP8& operator=(VP8&&) noexcept	= default;
			~VP8() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}