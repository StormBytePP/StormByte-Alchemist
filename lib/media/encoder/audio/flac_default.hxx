#include "../audio.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC FLAC_DEFAULT final: public Base {
		public:
			FLAC_DEFAULT();
			FLAC_DEFAULT(const FLAC_DEFAULT&)				= default;
			FLAC_DEFAULT(FLAC_DEFAULT&&)					= default;
			FLAC_DEFAULT& operator=(const FLAC_DEFAULT&)	= default;
			FLAC_DEFAULT& operator=(FLAC_DEFAULT&&)			= default;
			~FLAC_DEFAULT()									= default;
	};
}