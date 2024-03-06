#include "../video.hxx"

namespace Alchemist::Media::Decoder {
	class DLL_PUBLIC H264_CUVID final: public Video {
		public:
			H264_CUVID();
			H264_CUVID(const H264_CUVID&)				= default;
			H264_CUVID(H264_CUVID&&)					= default;
			H264_CUVID& operator=(const H264_CUVID&)	= default;
			H264_CUVID& operator=(H264_CUVID&&)		= default;
			~H264_CUVID()								= default;
	};
}