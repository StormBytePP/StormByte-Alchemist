#include <Alchemy/media/subtitle/codec/subrip.hxx>

using namespace Alchemy::Media::Subtitle;

Subrip::Subrip() noexcept:Codec("subrip", "subrip", "Subrip subtitles") { m_supported = false; }