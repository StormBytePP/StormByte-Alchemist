#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC JPG final: public Base {
		public:
			JPG();
			JPG(const JPG&)					= default;
			JPG(JPG&&)						= default;
			JPG& operator=(const JPG&)		= default;
			JPG& operator=(JPG&&)			= default;
			~JPG()							= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}