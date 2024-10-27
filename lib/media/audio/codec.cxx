#ifdef ENABLE_FDK
#include "codec/aac.hxx"
#endif
#include "codec/copy.hxx"

using namespace Alchemist::Media::Audio;

Codec::Codec(std::string&& name, std::string&& ffmpeg_name, std::string&& desc) noexcept:
Media::Codec(std::move(name), std::move(ffmpeg_name), std::move(desc)) {}

Codec::~Codec() noexcept {}

const std::list<std::shared_ptr<Codec>> Codec::All = {
	#ifdef ENABLE_FDK
	std::make_shared<AAC>(),
	#endif
	std::make_shared<Copy>(),
};