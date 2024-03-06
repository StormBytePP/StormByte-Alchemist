#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC VP8 final: public Audio {
		public:
			VP8();
			VP8(const VP8&)					= default;
			VP8(VP8&&)						= default;
			VP8& operator=(const VP8&)		= default;
			VP8& operator=(VP8&&)			= default;
			~VP8()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}