#include "media/decoder.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC Audio: public Media::Decoder::Base {
		public:
			Audio(const Media::Decoder::Type&);
			Audio(Media::Decoder::Type&&);
			Audio(const Audio&)				= default;
			Audio(Audio&&)					= default;
			Audio& operator=(const Audio&)	= default;
			Audio& operator=(Audio&&)		= default;
			virtual ~Audio()				= 0;
	};
}