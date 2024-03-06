#include "../video.hxx"

namespace Alchemist::Media::Decoder {
	class DLL_PUBLIC AV1_DEFAULT final: public Video {
		public:
			AV1_DEFAULT();
			AV1_DEFAULT(const AV1_DEFAULT&)				= default;
			AV1_DEFAULT(AV1_DEFAULT&&)					= default;
			AV1_DEFAULT& operator=(const AV1_DEFAULT&)	= default;
			AV1_DEFAULT& operator=(AV1_DEFAULT&&)		= default;
			~AV1_DEFAULT()								= default;
	};
}