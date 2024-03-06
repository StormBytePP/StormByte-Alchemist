#include "../video.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC AV1_DAV1D final: public Video {
		public:
			AV1_DAV1D();
			AV1_DAV1D(const AV1_DAV1D&)				= default;
			AV1_DAV1D(AV1_DAV1D&&)					= default;
			AV1_DAV1D& operator=(const AV1_DAV1D&)	= default;
			AV1_DAV1D& operator=(AV1_DAV1D&&)		= default;
			~AV1_DAV1D()								= default;
	};
}