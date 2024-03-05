#include "media/codec/audio.hxx"

namespace StormByte::Alchemist::Media::Codec {
	class DLL_PUBLIC VORBIS final: public Audio {
		public:
			VORBIS();
			VORBIS(const VORBIS&)					= default;
			VORBIS(VORBIS&&)						= default;
			VORBIS& operator=(const VORBIS&)		= default;
			VORBIS& operator=(VORBIS&&)			= default;
			~VORBIS()							= default;
	};
}