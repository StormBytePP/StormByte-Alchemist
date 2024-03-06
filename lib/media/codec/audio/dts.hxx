#include "media/codec/audio.hxx"

namespace Alchemist::Media::Codec {
	class DLL_PUBLIC DTS final: public Audio {
		public:
			DTS();
			DTS(const DTS&)					= default;
			DTS(DTS&&)						= default;
			DTS& operator=(const DTS&)		= default;
			DTS& operator=(DTS&&)			= default;
			~DTS()							= default;
	};
}