#include "../audio.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC AAC_FDK final: public Audio {
		public:
			AAC_FDK();
			AAC_FDK(const AAC_FDK&)				= default;
			AAC_FDK(AAC_FDK&&)					= default;
			AAC_FDK& operator=(const AAC_FDK&)	= default;
			AAC_FDK& operator=(AAC_FDK&&)		= default;
			~AAC_FDK()								= default;
	};
}