#include "../video.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC AV1_SVT final: public Video {
		public:
			AV1_SVT();
			AV1_SVT(const AV1_SVT&)				= default;
			AV1_SVT(AV1_SVT&&)					= default;
			AV1_SVT& operator=(const AV1_SVT&)	= default;
			AV1_SVT& operator=(AV1_SVT&&)		= default;
			~AV1_SVT()							= default;
	};
}