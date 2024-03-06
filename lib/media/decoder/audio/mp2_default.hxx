#include "../audio.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC MP2_DEFAULT final: public Audio {
		public:
			MP2_DEFAULT();
			MP2_DEFAULT(const MP2_DEFAULT&)				= default;
			MP2_DEFAULT(MP2_DEFAULT&&)					= default;
			MP2_DEFAULT& operator=(const MP2_DEFAULT&)	= default;
			MP2_DEFAULT& operator=(MP2_DEFAULT&&)		= default;
			~MP2_DEFAULT()								= default;
	};
}