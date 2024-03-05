#include "media/codec/audio.hxx"

namespace StormByte::Alchemist::Media::Codec {
	class DLL_PUBLIC AAC final: public Audio {
		public:
			AAC();
			AAC(const AAC&)					= default;
			AAC(AAC&&)						= default;
			AAC& operator=(const AAC&)		= default;
			AAC& operator=(AAC&&)			= default;
			~AAC()							= default;
	};
}