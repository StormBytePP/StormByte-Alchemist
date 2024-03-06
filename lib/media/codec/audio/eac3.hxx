#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC EAC3 final: public Audio {
		public:
			EAC3();
			EAC3(const EAC3&)					= default;
			EAC3(EAC3&&)						= default;
			EAC3& operator=(const EAC3&)		= default;
			EAC3& operator=(EAC3&&)				= default;
			~EAC3()								= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}