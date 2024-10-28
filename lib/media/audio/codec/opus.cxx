#include "opus.hxx"

using namespace Alchemist::Media::Audio;

OPUS::OPUS() noexcept:Codec("OPUS", "libopus", "Opus") {
	#ifndef ENABLE_LIBOPUS
	m_supported = false;
	#endif
}