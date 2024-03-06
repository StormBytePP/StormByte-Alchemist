#include "media/codec.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC Audio: public Base {
		public:
			Audio(const Codec::Type&);
			Audio(Codec::Type&&);
			Audio(const Audio&)				= default;
			Audio(Audio&&)					= default;
			Audio& operator=(const Audio&)	= default;
			Audio& operator=(Audio&&)		= default;
			virtual ~Audio()				= default;

			bool is_video() const;
			bool is_audio() const;
			bool is_image() const;
	};
}