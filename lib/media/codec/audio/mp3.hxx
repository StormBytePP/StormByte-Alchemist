#include "media/codec/audio.hxx"

namespace StormByte::Alchemist::Media::Codec {
	class DLL_PUBLIC MP3 final: public Audio {
		public:
			MP3();
			MP3(const MP3&)					= default;
			MP3(MP3&&)						= default;
			MP3& operator=(const MP3&)		= default;
			MP3& operator=(MP3&&)			= default;
			~MP3()							= default;
	};
}