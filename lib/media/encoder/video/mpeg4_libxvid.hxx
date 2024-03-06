#include "../video.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC MPEG4_LIBXVID final: public Video {
		public:
			MPEG4_LIBXVID();
			MPEG4_LIBXVID(const MPEG4_LIBXVID&)				= default;
			MPEG4_LIBXVID(MPEG4_LIBXVID&&)					= default;
			MPEG4_LIBXVID& operator=(const MPEG4_LIBXVID&)	= default;
			MPEG4_LIBXVID& operator=(MPEG4_LIBXVID&&)		= default;
			~MPEG4_LIBXVID()							= default;
	};
}