#include "h264.hxx"

using namespace Alchemist::Media::Video;

H264::H264() noexcept:Codec("H264", "libx264", "H.264 / AVC / MPEG-4 AVC / MPEG-4 part 10") {
	#ifndef ENABLE_H264
	m_supported = false;
	#endif
}