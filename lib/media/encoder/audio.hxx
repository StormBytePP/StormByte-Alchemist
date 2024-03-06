#include "media/encoder.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC Audio: public Media::Encoder::Base {
		public:
			Audio(const Media::Encoder::Type&);
			Audio(Media::Encoder::Type&&);
			Audio(const Audio&)				= default;
			Audio(Audio&&)					= default;
			Audio& operator=(const Audio&)	= default;
			Audio& operator=(Audio&&)		= default;
			virtual ~Audio()				= 0;
	};
}