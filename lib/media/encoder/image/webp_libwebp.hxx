#include "../image.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC WEBP_LIBWEBP final: public Image {
		public:
			WEBP_LIBWEBP();
			WEBP_LIBWEBP(const WEBP_LIBWEBP&)				= default;
			WEBP_LIBWEBP(WEBP_LIBWEBP&&)					= default;
			WEBP_LIBWEBP& operator=(const WEBP_LIBWEBP&)	= default;
			WEBP_LIBWEBP& operator=(WEBP_LIBWEBP&&)			= default;
			~WEBP_LIBWEBP()											= default;
	};
}