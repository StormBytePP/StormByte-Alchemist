#include "../image.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC GIF_DEFAULT final: public Image {
		public:
			GIF_DEFAULT();
			GIF_DEFAULT(const GIF_DEFAULT&)				= default;
			GIF_DEFAULT(GIF_DEFAULT&&)					= default;
			GIF_DEFAULT& operator=(const GIF_DEFAULT&)	= default;
			GIF_DEFAULT& operator=(GIF_DEFAULT&&)		= default;
			~GIF_DEFAULT()								= default;
	};
}