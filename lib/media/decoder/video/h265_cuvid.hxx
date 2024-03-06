#include "../video.hxx"

namespace Alchemist::Media::Decoder {
	class DLL_PUBLIC H265_CUVID final: public Video {
		public:
			H265_CUVID();
			H265_CUVID(const H265_CUVID&)				= default;
			H265_CUVID(H265_CUVID&&)					= default;
			H265_CUVID& operator=(const H265_CUVID&)	= default;
			H265_CUVID& operator=(H265_CUVID&&)		= default;
			~H265_CUVID()								= default;
	};
}