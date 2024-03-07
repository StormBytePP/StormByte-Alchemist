#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC PNG final: public Base {
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