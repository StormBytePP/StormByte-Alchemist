#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC VP8_LIBVPX final: public Base {
		public:
			VP8_LIBVPX();
			VP8_LIBVPX(const VP8_LIBVPX&)				= default;
			VP8_LIBVPX(VP8_LIBVPX&&)					= default;
			VP8_LIBVPX& operator=(const VP8_LIBVPX&)	= default;
			VP8_LIBVPX& operator=(VP8_LIBVPX&&)		= default;
			~VP8_LIBVPX()							= default;
	};
}