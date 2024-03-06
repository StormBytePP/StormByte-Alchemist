#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC JPG final: public Audio {
		public:
			JPG();
			JPG(const JPG&)					= default;
			JPG(JPG&&)						= default;
			JPG& operator=(const JPG&)		= default;
			JPG& operator=(JPG&&)			= default;
			~JPG()							= default;
	};
}