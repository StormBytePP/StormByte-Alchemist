#include <Alchemy/media/subtitle/codec/pgs.hxx>

using namespace Alchemy::Media::Subtitle;

PGS::PGS() noexcept:Codec("PGS", "hdmv_pgs_subtitle", "HDMV Presentation Graphic Stream subtitles") { m_supported = false; }