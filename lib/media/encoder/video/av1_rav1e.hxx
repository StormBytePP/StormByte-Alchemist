#include "../video.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC AV1_RAV1E final: public Video {
		public:
			AV1_RAV1E();
			AV1_RAV1E(const AV1_RAV1E&)				= default;
			AV1_RAV1E(AV1_RAV1E&&)					= default;
			AV1_RAV1E& operator=(const AV1_RAV1E&)	= default;
			AV1_RAV1E& operator=(AV1_RAV1E&&)		= default;
			~AV1_RAV1E()							= default;
	};
}