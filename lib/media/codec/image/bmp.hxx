#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC BMP final: public Audio {
		public:
			BMP();
			BMP(const BMP&)					= default;
			BMP(BMP&&)						= default;
			BMP& operator=(const BMP&)		= default;
			BMP& operator=(BMP&&)			= default;
			~BMP()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}