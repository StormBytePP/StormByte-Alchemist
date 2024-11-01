#include <Alchemy/media/subtitle/codec/subrip.hxx>

using namespace Alchemist::Media::Subtitle;

Subrip::Subrip() noexcept:Codec("subrip", "subrip", "Subrip subtitles") { m_supported = false; }