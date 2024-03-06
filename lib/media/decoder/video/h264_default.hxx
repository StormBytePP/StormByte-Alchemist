#include "../video.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC H264_DEFAULT final: public Video {
		public:
			H264_DEFAULT();
			H264_DEFAULT(const H264_DEFAULT&)				= default;
			H264_DEFAULT(H264_DEFAULT&&)					= default;
			H264_DEFAULT& operator=(const H264_DEFAULT&)	= default;
			H264_DEFAULT& operator=(H264_DEFAULT&&)		= default;
			~H264_DEFAULT()								= default;
	};
}