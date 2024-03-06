#include "../encoder.hxx"

namespace Alchemist::Media::Encoder {
	class DLL_PUBLIC Image: public Media::Encoder::Base {
		public:
			Image(const Media::Encoder::Type&);
			Image(Media::Encoder::Type&&);
			Image(const Image&)				= default;
			Image(Image&&)					= default;
			Image& operator=(const Image&)	= default;
			Image& operator=(Image&&)		= default;
			virtual ~Image()				= 0;
	};
}