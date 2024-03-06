#include "../decoder.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC Video: public Media::Decoder::Base {
		public:
			Video(const Media::Decoder::Type&);
			Video(Media::Decoder::Type&&);
			Video(const Video&)				= default;
			Video(Video&&)					= default;
			Video& operator=(const Video&)	= default;
			Video& operator=(Video&&)		= default;
			virtual ~Video()				= 0;
	};
}