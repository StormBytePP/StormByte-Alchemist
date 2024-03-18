#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Codec::Video {
	class DLL_PUBLIC MPEG4 final: public Base {
		public:
			MPEG4();
			MPEG4(const MPEG4&)					= default;
			MPEG4(MPEG4&&) noexcept				= default;
			MPEG4& operator=(const MPEG4&)		= default;
			MPEG4& operator=(MPEG4&&) noexcept	= default;
			~MPEG4() noexcept					= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}