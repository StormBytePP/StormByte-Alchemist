#include "../audio.hxx"

namespace Alchemist::Media::Codec::Encoder {
	class DLL_PUBLIC AC3_DEFAULT final: public Audio {
		public:
			AC3_DEFAULT();
			AC3_DEFAULT(const AC3_DEFAULT&)				= default;
			AC3_DEFAULT(AC3_DEFAULT&&)					= default;
			AC3_DEFAULT& operator=(const AC3_DEFAULT&)	= default;
			AC3_DEFAULT& operator=(AC3_DEFAULT&&)		= default;
			~AC3_DEFAULT()								= default;
	};
}