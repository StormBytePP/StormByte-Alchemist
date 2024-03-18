#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Encoder::Image {
	class DLL_PUBLIC WEBP_LIBWEBP final: public Base {
		public:
			WEBP_LIBWEBP();
			WEBP_LIBWEBP(const WEBP_LIBWEBP&)				= default;
			WEBP_LIBWEBP(WEBP_LIBWEBP&&) noexcept			= default;
			WEBP_LIBWEBP& operator=(const WEBP_LIBWEBP&)	= default;
			WEBP_LIBWEBP& operator=(WEBP_LIBWEBP&&) noexcept= default;
			~WEBP_LIBWEBP() noexcept						= default;
	};
}