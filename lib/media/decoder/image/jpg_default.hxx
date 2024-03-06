#include "../image.hxx"

namespace Alchemist::Media::Decoder {
	class DLL_PUBLIC JPG_DEFAULT final: public Image {
		public:
			JPG_DEFAULT();
			JPG_DEFAULT(const JPG_DEFAULT&)				= default;
			JPG_DEFAULT(JPG_DEFAULT&&)					= default;
			JPG_DEFAULT& operator=(const JPG_DEFAULT&)	= default;
			JPG_DEFAULT& operator=(JPG_DEFAULT&&)		= default;
			~JPG_DEFAULT()								= default;
	};
}