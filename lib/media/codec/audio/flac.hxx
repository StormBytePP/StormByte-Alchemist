#include "media/codec/audio.hxx"

namespace StormByte::Alchemist::Media::Codec {
	class DLL_PUBLIC FLAC final: public Audio {
		public:
			FLAC();
			FLAC(const FLAC&)					= default;
			FLAC(FLAC&&)						= default;
			FLAC& operator=(const FLAC&)		= default;
			FLAC& operator=(FLAC&&)			= default;
			~FLAC()							= default;
	};
}