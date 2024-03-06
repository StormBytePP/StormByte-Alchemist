#include "../video.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC VP8_LIBVPX final: public Video {
		public:
			VP8_LIBVPX();
			VP8_LIBVPX(const VP8_LIBVPX&)				= default;
			VP8_LIBVPX(VP8_LIBVPX&&)					= default;
			VP8_LIBVPX& operator=(const VP8_LIBVPX&)	= default;
			VP8_LIBVPX& operator=(VP8_LIBVPX&&)		= default;
			~VP8_LIBVPX()							= default;
	};
}