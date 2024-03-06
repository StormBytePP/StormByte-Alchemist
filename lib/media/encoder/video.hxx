#include "../encoder.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC Video: public Media::Encoder::Base {
		public:
			Video(const Media::Encoder::Type&);
			Video(Media::Encoder::Type&&);
			Video(const Video&)				= default;
			Video(Video&&)					= default;
			Video& operator=(const Video&)	= default;
			Video& operator=(Video&&)		= default;
			virtual ~Video()				= 0;
	};
}