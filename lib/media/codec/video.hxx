#include "media/codec.hxx"

namespace StormByte::Alchemist::Media::Codec {
	class DLL_PUBLIC Video: public Base {
		public:
			Video(const Codec::Type&);
			Video(Codec::Type&&);
			Video(const Video&)				= default;
			Video(Video&&)					= default;
			Video& operator=(const Video&)	= default;
			Video& operator=(Video&&)		= default;
			virtual ~Video()				= 0;

			bool is_video() const;
			bool is_audio() const;
			bool is_image() const;
	};
}