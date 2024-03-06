#include "../audio.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC DTS_DEFAULT final: public Audio {
		public:
			DTS_DEFAULT();
			DTS_DEFAULT(const DTS_DEFAULT&)				= default;
			DTS_DEFAULT(DTS_DEFAULT&&)					= default;
			DTS_DEFAULT& operator=(const DTS_DEFAULT&)	= default;
			DTS_DEFAULT& operator=(DTS_DEFAULT&&)		= default;
			~DTS_DEFAULT()								= default;
	};
}