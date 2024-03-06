#include "../decoder.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC Image: public Media::Decoder::Base {
		public:
			Image(const Media::Decoder::Type&);
			Image(Media::Decoder::Type&&);
			Image(const Image&)				= default;
			Image(Image&&)					= default;
			Image& operator=(const Image&)	= default;
			Image& operator=(Image&&)		= default;
			virtual ~Image()				= 0;
	};
}