#include <Alchemy/media/audio/codec/opus.hxx>

using namespace Alchemy::Media::Audio;

OPUS::OPUS() noexcept:Codec("OPUS", "libopus", "Opus") {
	#ifndef ENABLE_LIBOPUS
	m_supported = false;
	#endif
}