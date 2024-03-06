#include "../video.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC VP9_CUVID final: public Video {
		public:
			VP9_CUVID();
			VP9_CUVID(const VP9_CUVID&)				= default;
			VP9_CUVID(VP9_CUVID&&)					= default;
			VP9_CUVID& operator=(const VP9_CUVID&)	= default;
			VP9_CUVID& operator=(VP9_CUVID&&)		= default;
			~VP9_CUVID()								= default;
	};
}