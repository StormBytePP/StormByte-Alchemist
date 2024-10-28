#include "pgs.hxx"

using namespace Alchemist::Media::Subtitle;

PGS::PGS() noexcept:Codec("PGS", "hdmv_pgs_subtitle", "HDMV Presentation Graphic Stream subtitles") { m_supported = false; }