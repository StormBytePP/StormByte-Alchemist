#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC AAC final: public Base {
		public:
			AAC();
			AAC(const AAC&)					= default;
			AAC(AAC&&)						= default;
			AAC& operator=(const AAC&)		= default;
			AAC& operator=(AAC&&)			= default;
			~AAC()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}