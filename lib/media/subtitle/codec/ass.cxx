#include "ass.hxx"

using namespace Alchemist::Media::Subtitle;

ASS::ASS() noexcept:Codec("ASS", "ass", "ASS (Advanced SSA) subtitle") { m_supported = false; }