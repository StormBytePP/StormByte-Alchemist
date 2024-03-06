#include "../audio.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC EAC3_DEFAULT final: public Audio {
		public:
			EAC3_DEFAULT();
			EAC3_DEFAULT(const EAC3_DEFAULT&)				= default;
			EAC3_DEFAULT(EAC3_DEFAULT&&)					= default;
			EAC3_DEFAULT& operator=(const EAC3_DEFAULT&)	= default;
			EAC3_DEFAULT& operator=(EAC3_DEFAULT&&)		= default;
			~EAC3_DEFAULT()								= default;
	};
}