#include "../audio.hxx"

namespace Alchemist::Media::Decoder {
	class DLL_PUBLIC MP3_DEFAULT final: public Audio {
		public:
			MP3_DEFAULT();
			MP3_DEFAULT(const MP3_DEFAULT&)				= default;
			MP3_DEFAULT(MP3_DEFAULT&&)					= default;
			MP3_DEFAULT& operator=(const MP3_DEFAULT&)	= default;
			MP3_DEFAULT& operator=(MP3_DEFAULT&&)		= default;
			~MP3_DEFAULT()								= default;
	};
}