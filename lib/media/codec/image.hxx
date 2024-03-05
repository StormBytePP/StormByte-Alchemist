#include "media/codec.hxx"

namespace StormByte::Alchemist::Media::Codec {
	class DLL_PUBLIC Image: public Base {
		public:
			Image(const Codec::Type&);
			Image(Codec::Type&&);
			Image(const Image&)				= default;
			Image(Image&&)					= default;
			Image& operator=(const Image&)	= default;
			Image& operator=(Image&&)		= default;
			virtual ~Image()				= 0;

			bool is_video() const;
			bool is_audio() const;
			bool is_image() const;
	};
}