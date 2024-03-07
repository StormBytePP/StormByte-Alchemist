#include "../video.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC AV1_CUVID final: public Base {
		public:
			AV1_CUVID();
			AV1_CUVID(const AV1_CUVID&)				= default;
			AV1_CUVID(AV1_CUVID&&)					= default;
			AV1_CUVID& operator=(const AV1_CUVID&)	= default;
			AV1_CUVID& operator=(AV1_CUVID&&)		= default;
			~AV1_CUVID()							= default;
	};
}