#include "../image.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC TIFF final: public Base {
		public:
			TIFF();
			TIFF(const TIFF&)					= default;
			TIFF(TIFF&&)						= default;
			TIFF& operator=(const TIFF&)		= default;
			TIFF& operator=(TIFF&&)				= default;
			~TIFF()								= default;

			std::list<Decoder::Type> get_available_decoders() const;
			std::list<Encoder::Type> get_available_encoders() const;
	};
}