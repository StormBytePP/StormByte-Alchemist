#include "../audio.hxx"

namespace Alchemist::Media::Decoder::Audio {
	class DLL_PUBLIC OPUS_LIBOPUS final: public Base {
		public:
			OPUS_LIBOPUS();
			OPUS_LIBOPUS(const OPUS_LIBOPUS&)				= default;
			OPUS_LIBOPUS(OPUS_LIBOPUS&&)					= default;
			OPUS_LIBOPUS& operator=(const OPUS_LIBOPUS&)	= default;
			OPUS_LIBOPUS& operator=(OPUS_LIBOPUS&&)		= default;
			~OPUS_LIBOPUS()								= default;
	};
}