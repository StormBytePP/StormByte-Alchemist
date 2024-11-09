#include <Alchemy/media/audio/codec/atmos.hxx>

using namespace Alchemy::Media::Audio;

Atmos::Atmos() noexcept:Codec("Dolby Atmos", "truehd", "Dolby Atmos + Dolby Atmos") { m_supported = false; }