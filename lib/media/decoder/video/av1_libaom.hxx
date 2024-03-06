#include "../video.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC AV1_LIBAOM final: public Video {
		public:
			AV1_LIBAOM();
			AV1_LIBAOM(const AV1_LIBAOM&)				= default;
			AV1_LIBAOM(AV1_LIBAOM&&)					= default;
			AV1_LIBAOM& operator=(const AV1_LIBAOM&)	= default;
			AV1_LIBAOM& operator=(AV1_LIBAOM&&)		= default;
			~AV1_LIBAOM()							= default;
	};
}