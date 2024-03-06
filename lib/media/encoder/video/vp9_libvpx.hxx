#include "../video.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC VP9_LIBVPX final: public Video {
		public:
			VP9_LIBVPX();
			VP9_LIBVPX(const VP9_LIBVPX&)				= default;
			VP9_LIBVPX(VP9_LIBVPX&&)					= default;
			VP9_LIBVPX& operator=(const VP9_LIBVPX&)	= default;
			VP9_LIBVPX& operator=(VP9_LIBVPX&&)		= default;
			~VP9_LIBVPX()							= default;
	};
}