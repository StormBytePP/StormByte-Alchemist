#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC MPEG2_DEFAULT final: public Base {
		public:
			MPEG2_DEFAULT();
			MPEG2_DEFAULT(const MPEG2_DEFAULT&)				= default;
			MPEG2_DEFAULT(MPEG2_DEFAULT&&)					= default;
			MPEG2_DEFAULT& operator=(const MPEG2_DEFAULT&)	= default;
			MPEG2_DEFAULT& operator=(MPEG2_DEFAULT&&)		= default;
			~MPEG2_DEFAULT()							= default;
	};
}