#include <Alchemy/media/subtitle/codec/ass.hxx>

using namespace Alchemy::Media::Subtitle;

ASS::ASS() noexcept:Codec("ASS", "ass", "ASS (Advanced SSA) subtitle") { m_supported = false; }