#include "../audio.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC AAC_FRAUNHOFFER final: public Audio {
		public:
			AAC_FRAUNHOFFER();
			AAC_FRAUNHOFFER(const AAC_FRAUNHOFFER&)				= default;
			AAC_FRAUNHOFFER(AAC_FRAUNHOFFER&&)					= default;
			AAC_FRAUNHOFFER& operator=(const AAC_FRAUNHOFFER&)	= default;
			AAC_FRAUNHOFFER& operator=(AAC_FRAUNHOFFER&&)		= default;
			~AAC_FRAUNHOFFER()									= default;
	};
}