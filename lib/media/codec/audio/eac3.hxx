#include "../audio.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC EAC3 final: public Base {
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