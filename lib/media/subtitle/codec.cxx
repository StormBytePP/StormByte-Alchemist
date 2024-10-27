#include "codec/copy.hxx"

using namespace Alchemist::Media::Subtitle;

Codec::Codec(std::string&& name, std::string&& ffmpeg_name, std::string&& desc) noexcept:
Media::Codec(std::move(name), std::move(ffmpeg_name), std::move(desc)) {}

Codec::~Codec() noexcept {}

const std::list<std::shared_ptr<Codec>> Codec::All = {
	std::make_shared<Copy>(),
};