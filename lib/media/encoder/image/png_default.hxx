#include "../image.hxx"

namespace Alchemist::Media::Encoder {
	class DLL_PUBLIC PNG_DEFAULT final: public Image {
		public:
			PNG_DEFAULT();
			PNG_DEFAULT(const PNG_DEFAULT&)				= default;
			PNG_DEFAULT(PNG_DEFAULT&&)					= default;
			PNG_DEFAULT& operator=(const PNG_DEFAULT&)	= default;
			PNG_DEFAULT& operator=(PNG_DEFAULT&&)		= default;
			~PNG_DEFAULT()								= default;
	};
}