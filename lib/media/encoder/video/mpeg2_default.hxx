#include "../video.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC MPEG2_DEFAULT final: public Video {
		public:
			MPEG2_DEFAULT();
			MPEG2_DEFAULT(const MPEG2_DEFAULT&)				= default;
			MPEG2_DEFAULT(MPEG2_DEFAULT&&)					= default;
			MPEG2_DEFAULT& operator=(const MPEG2_DEFAULT&)	= default;
			MPEG2_DEFAULT& operator=(MPEG2_DEFAULT&&)		= default;
			~MPEG2_DEFAULT()							= default;
	};
}