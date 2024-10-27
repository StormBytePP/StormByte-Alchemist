#include "video.hxx"

using namespace Alchemist::Media;

Video::Video(std::shared_ptr<Codec> codec, const Metadata::Video& metadata):
Stream(std::move(codec)), m_metadata(metadata) {}

Video::Video(std::shared_ptr<Codec>&& codec, Metadata::Video&& metadata) noexcept:
Stream(std::move(codec)), m_metadata(std::move(metadata)) {}

const Metadata::Video& Video::GetMetadata() const noexcept { return m_metadata; }
