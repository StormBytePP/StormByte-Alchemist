#include "codec/ass.hxx"
#include "codec/copy.hxx"
#include "codec/pgs.hxx"
#include "codec/subrip.hxx"

using namespace Alchemist::Media::Subtitle;

Codec::Codec(std::string&& name, std::string&& ffmpeg_name, std::string&& desc) noexcept:
Media::Codec(std::move(name), std::move(ffmpeg_name), std::move(desc)) {}

Codec::~Codec() noexcept {}

const std::map<std::string, std::shared_ptr<Codec>> Codec::All = {
	{ "ass",				std::make_shared<ASS>()		},
	{ "copy",				std::make_shared<Copy>()	},
	{ "hdmv_pgs_subtitle",	std::make_shared<PGS>()		},
	{ "subrip",				std::make_shared<Subrip>()	}
};