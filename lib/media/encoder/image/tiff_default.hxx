#include "../image.hxx"

namespace Alchemist::Media::Encoder::Image {
	class DLL_PUBLIC TIFF_DEFAULT final: public Base {
		public:
			TIFF_DEFAULT();
			TIFF_DEFAULT(const TIFF_DEFAULT&)				= default;
			TIFF_DEFAULT(TIFF_DEFAULT&&)					= default;
			TIFF_DEFAULT& operator=(const TIFF_DEFAULT&)	= default;
			TIFF_DEFAULT& operator=(TIFF_DEFAULT&&)			= default;
			~TIFF_DEFAULT()									= default;
	};
}