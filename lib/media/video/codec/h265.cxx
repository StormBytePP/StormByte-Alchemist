#include "h265.hxx"

using namespace Alchemist::Media::Video;

H265::H265() noexcept:Codec("H265", "libx265", "H.265 / HEVC (High Efficiency Video Coding") {
	#ifndef ENABLE_H265
	m_supported = false;
	#endif
}