#include "../video.hxx"

namespace Alchemist::Media::Codec::Decoder {
	class DLL_PUBLIC H264_OPENH264 final: public Video {
		public:
			H264_OPENH264();
			H264_OPENH264(const H264_OPENH264&)				= default;
			H264_OPENH264(H264_OPENH264&&)					= default;
			H264_OPENH264& operator=(const H264_OPENH264&)	= default;
			H264_OPENH264& operator=(H264_OPENH264&&)		= default;
			~H264_OPENH264()								= default;
	};
}