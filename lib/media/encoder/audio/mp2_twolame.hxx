#include "../audio.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC MP2_TWOLAME final: public Audio {
		public:
			MP2_TWOLAME();
			MP2_TWOLAME(const MP2_TWOLAME&)				= default;
			MP2_TWOLAME(MP2_TWOLAME&&)					= default;
			MP2_TWOLAME& operator=(const MP2_TWOLAME&)	= default;
			MP2_TWOLAME& operator=(MP2_TWOLAME&&)		= default;
			~MP2_TWOLAME()								= default;
	};
}