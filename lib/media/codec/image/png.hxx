#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC PNG final: public Audio {
		public:
			PNG();
			PNG(const PNG&)					= default;
			PNG(PNG&&)						= default;
			PNG& operator=(const PNG&)		= default;
			PNG& operator=(PNG&&)			= default;
			~PNG()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}