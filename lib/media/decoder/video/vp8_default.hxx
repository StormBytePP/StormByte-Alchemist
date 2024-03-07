#include "../video.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC VP8_DEFAULT final: public Base {
		public:
			VP8_DEFAULT();
			VP8_DEFAULT(const VP8_DEFAULT&)				= default;
			VP8_DEFAULT(VP8_DEFAULT&&)					= default;
			VP8_DEFAULT& operator=(const VP8_DEFAULT&)	= default;
			VP8_DEFAULT& operator=(VP8_DEFAULT&&)		= default;
			~VP8_DEFAULT()								= default;
	};
}