#include "../video.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC AV1_CUVID final: public Video {
		public:
			AV1_CUVID();
			AV1_CUVID(const AV1_CUVID&)				= default;
			AV1_CUVID(AV1_CUVID&&)					= default;
			AV1_CUVID& operator=(const AV1_CUVID&)	= default;
			AV1_CUVID& operator=(AV1_CUVID&&)		= default;
			~AV1_CUVID()							= default;
	};
}