#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC WEBP final: public Audio {
		public:
			WEBP();
			WEBP(const WEBP&)					= default;
			WEBP(WEBP&&)						= default;
			WEBP& operator=(const WEBP&)		= default;
			WEBP& operator=(WEBP&&)			= default;
			~WEBP()							= default;
	};
}