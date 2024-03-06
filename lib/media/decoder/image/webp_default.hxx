#include "../image.hxx"

namespace Alchemist::Media::Decoder {
	class DLL_PUBLIC WEBP_DEFAULT final: public Image {
		public:
			WEBP_DEFAULT();
			WEBP_DEFAULT(const WEBP_DEFAULT&)				= default;
			WEBP_DEFAULT(WEBP_DEFAULT&&)					= default;
			WEBP_DEFAULT& operator=(const WEBP_DEFAULT&)	= default;
			WEBP_DEFAULT& operator=(WEBP_DEFAULT&&)			= default;
			~WEBP_DEFAULT()									= default;
	};
}