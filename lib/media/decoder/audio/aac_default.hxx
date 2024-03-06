#include "../audio.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC AAC_DEFAULT final: public Audio {
		public:
			AAC_DEFAULT();
			AAC_DEFAULT(const AAC_DEFAULT&)				= default;
			AAC_DEFAULT(AAC_DEFAULT&&)					= default;
			AAC_DEFAULT& operator=(const AAC_DEFAULT&)	= default;
			AAC_DEFAULT& operator=(AAC_DEFAULT&&)		= default;
			~AAC_DEFAULT()								= default;
	};
}