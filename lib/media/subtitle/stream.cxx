#include "stream.hxx"

using namespace Alchemist::Media::Subtitle;

Stream::Stream(std::shared_ptr<Codec> codec, const Metadata& metadata):
Media::Stream(codec, std::make_shared<Metadata>(metadata)) {}

Stream::Stream(std::shared_ptr<Codec> codec, Metadata&& metadata) noexcept:
Media::Stream(codec, std::make_shared<Metadata>(std::move(metadata))) {}

Stream::Stream(std::shared_ptr<Codec> codec, std::shared_ptr<Metadata> metadata) noexcept:
Media::Stream(codec, metadata) {}
