#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC TIFF final: public Audio {
		public:
			TIFF();
			TIFF(const TIFF&)					= default;
			TIFF(TIFF&&)						= default;
			TIFF& operator=(const TIFF&)		= default;
			TIFF& operator=(TIFF&&)			= default;
			~TIFF()							= default;
	};
}