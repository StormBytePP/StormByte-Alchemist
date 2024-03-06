#include "../video.hxx"

namespace Alchemist::Media::Encoder {
	class DLL_PUBLIC AV1_NVENC final: public Video {
		public:
			AV1_NVENC();
			AV1_NVENC(const AV1_NVENC&)				= default;
			AV1_NVENC(AV1_NVENC&&)					= default;
			AV1_NVENC& operator=(const AV1_NVENC&)	= default;
			AV1_NVENC& operator=(AV1_NVENC&&)		= default;
			~AV1_NVENC()							= default;
	};
}