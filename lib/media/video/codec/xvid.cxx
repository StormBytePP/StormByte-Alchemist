#include "xvid.hxx"

using namespace Alchemist::Media::Video;

XVID::XVID() noexcept:Codec("XVID", "libx265", "H.265 / HEVC (High Efficiency Video Coding") {
	#ifndef ENABLE_XVID
	m_supported = false;
	#endif
}