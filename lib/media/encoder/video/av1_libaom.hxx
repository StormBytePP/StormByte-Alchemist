#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC AV1_LIBAOM final: public Base {
		public:
			AV1_LIBAOM();
			AV1_LIBAOM(const AV1_LIBAOM&)				= default;
			AV1_LIBAOM(AV1_LIBAOM&&) noexcept			= default;
			AV1_LIBAOM& operator=(const AV1_LIBAOM&)	= default;
			AV1_LIBAOM& operator=(AV1_LIBAOM&&) noexcept= default;
			~AV1_LIBAOM() noexcept						= default;
	};
}