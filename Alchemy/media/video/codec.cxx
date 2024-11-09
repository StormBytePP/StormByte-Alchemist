#include <Alchemy/media/video/codec/copy.hxx>
#include <Alchemy/media/video/codec/h264.hxx>
#include <Alchemy/media/video/codec/h265.hxx>
#include <Alchemy/media/video/codec/xvid.hxx>

using namespace Alchemy::Media::Video;

Codec::Codec(std::string&& name, std::string&& ffmpeg_name, std::string&& desc) noexcept:
Media::Codec(std::move(name), std::move(ffmpeg_name), std::move(desc)) {}

Codec::~Codec() noexcept {}

const std::map<std::string, std::shared_ptr<Codec>> Codec::All = {
	{ "copy",			std::make_shared<Copy>()	},
	{ "h264",			std::make_shared<H264>()	},
	{ "hevc",			std::make_shared<H265>()	},
	{ "mpeg4",			std::make_shared<XVID>()	}
};