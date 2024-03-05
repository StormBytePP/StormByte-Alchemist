#include "media/codec/audio.hxx"

namespace StormByte::Alchemist::Media::Codec {
	class DLL_PUBLIC OPUS final: public Audio {
		public:
			OPUS();
			OPUS(const OPUS&)					= default;
			OPUS(OPUS&&)						= default;
			OPUS& operator=(const OPUS&)		= default;
			OPUS& operator=(OPUS&&)			= default;
			~OPUS()							= default;
	};
}