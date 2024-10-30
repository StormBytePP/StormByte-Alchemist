#include "codec/aac.hxx"
#include "codec/ac3.hxx"
#include "codec/atmos.hxx"
#include "codec/copy.hxx"
#include "codec/dts.hxx"
#include "codec/eac3.hxx"
#include "codec/fdk_aac.hxx"
#include "codec/mp3.hxx"
#include "codec/wav.hxx"

using namespace Alchemist::Media::Audio;

Codec::Codec(std::string&& name, std::string&& ffmpeg_name, std::string&& desc) noexcept:
Media::Codec(std::move(name), std::move(ffmpeg_name), std::move(desc)) {}

Codec::~Codec() noexcept {}

const std::map<std::string, std::shared_ptr<Codec>> Codec::All = {
	{ "aac",		std::make_shared<AAC>()			},
	{ "ac3",		std::make_shared<AC3>()			},
	{ "copy",		std::make_shared<Copy>()		},
	{ "dts",		std::make_shared<DTS>()			},
	{ "eac3",		std::make_shared<EAC3>()			},
	{ "fdk_aac",	std::make_shared<FDK_AAC>()		},
	{ "mp3",		std::make_shared<MP3>()			},
	{ "truehd",		std::make_shared<Atmos>()		},
	{ "wav",		std::make_shared<WAV>()			}
};