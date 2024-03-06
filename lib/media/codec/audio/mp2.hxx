#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC MP2 final: public Audio {
		public:
			MP2();
			MP2(const MP2&)					= default;
			MP2(MP2&&)						= default;
			MP2& operator=(const MP2&)		= default;
			MP2& operator=(MP2&&)			= default;
			~MP2()							= default;
	};
}