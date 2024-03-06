#include "../video.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC H265_DEFAULT final: public Video {
		public:
			H265_DEFAULT();
			H265_DEFAULT(const H265_DEFAULT&)				= default;
			H265_DEFAULT(H265_DEFAULT&&)					= default;
			H265_DEFAULT& operator=(const H265_DEFAULT&)	= default;
			H265_DEFAULT& operator=(H265_DEFAULT&&)		= default;
			~H265_DEFAULT()								= default;
	};
}