#include "atmos.hxx"

using namespace Alchemist::Media::Audio;

Atmos::Atmos() noexcept:Codec("Dolby Atmos", "truehd", "Dolby Atmos + Dolby Atmos") { m_supported = false; }