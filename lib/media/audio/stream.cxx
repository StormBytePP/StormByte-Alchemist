#include "stream.hxx"

using namespace Alchemist::Media::Audio;

Stream::Stream(std::shared_ptr<Codec> codec, const Metadata& metadata):
Media::Stream(codec), m_metadata(metadata) {}

Stream::Stream(std::shared_ptr<Codec> codec, Metadata&& metadata) noexcept:
Media::Stream(codec), m_metadata(std::move(metadata)) {}

const Metadata& Stream::GetMetadata() const noexcept { return m_metadata; }
