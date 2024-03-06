#include "../video.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC AV1_AOM final: public Video {
		public:
			AV1_AOM();
			AV1_AOM(const AV1_AOM&)				= default;
			AV1_AOM(AV1_AOM&&)					= default;
			AV1_AOM& operator=(const AV1_AOM&)	= default;
			AV1_AOM& operator=(AV1_AOM&&)		= default;
			~AV1_AOM()							= default;
	};
}