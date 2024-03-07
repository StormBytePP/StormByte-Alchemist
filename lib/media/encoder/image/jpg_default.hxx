#include "../image.hxx"

namespace Alchemist::Media::Encoder::Image {
	class DLL_PUBLIC JPG_DEFAULT final: public Base {
		public:
			JPG_DEFAULT();
			JPG_DEFAULT(const JPG_DEFAULT&)				= default;
			JPG_DEFAULT(JPG_DEFAULT&&)					= default;
			JPG_DEFAULT& operator=(const JPG_DEFAULT&)	= default;
			JPG_DEFAULT& operator=(JPG_DEFAULT&&)		= default;
			~JPG_DEFAULT()								= default;
	};
}