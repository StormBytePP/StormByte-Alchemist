#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC H265_X265 final: public Base {
		public:
			H265_X265();
			H265_X265(const H265_X265&)				= default;
			H265_X265(H265_X265&&)					= default;
			H265_X265& operator=(const H265_X265&)	= default;
			H265_X265& operator=(H265_X265&&)		= default;
			~H265_X265()							= default;
	};
}