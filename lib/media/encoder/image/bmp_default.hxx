#include "../image.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC BMP_DEFAULT final: public Image {
		public:
			BMP_DEFAULT();
			BMP_DEFAULT(const BMP_DEFAULT&)				= default;
			BMP_DEFAULT(BMP_DEFAULT&&)					= default;
			BMP_DEFAULT& operator=(const BMP_DEFAULT&)	= default;
			BMP_DEFAULT& operator=(BMP_DEFAULT&&)		= default;
			~BMP_DEFAULT()								= default;
	};
}