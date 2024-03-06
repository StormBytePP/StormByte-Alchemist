#include "../video.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC VP9_DEFAULT final: public Video {
		public:
			VP9_DEFAULT();
			VP9_DEFAULT(const VP9_DEFAULT&)				= default;
			VP9_DEFAULT(VP9_DEFAULT&&)					= default;
			VP9_DEFAULT& operator=(const VP9_DEFAULT&)	= default;
			VP9_DEFAULT& operator=(VP9_DEFAULT&&)		= default;
			~VP9_DEFAULT()								= default;
	};
}