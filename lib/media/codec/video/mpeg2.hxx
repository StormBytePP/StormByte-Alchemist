#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC MPEG2 final: public Audio {
		public:
			MPEG2();
			MPEG2(const MPEG2&)					= default;
			MPEG2(MPEG2&&)						= default;
			MPEG2& operator=(const MPEG2&)		= default;
			MPEG2& operator=(MPEG2&&)			= default;
			~MPEG2()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}