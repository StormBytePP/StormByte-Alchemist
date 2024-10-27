#include "video.hxx"

using namespace Alchemist::Media;

VideoStream::VideoStream(std::unique_ptr<VideoCodec>&& codec, const Metadata::Video& metadata):
Stream(std::move(codec)), m_metadata(metadata) {}

VideoStream::VideoStream(std::unique_ptr<VideoCodec>&& codec, Metadata::Video&& metadata) noexcept:
Stream(std::move(codec)), m_metadata(std::move(metadata)) {}

const Metadata::Video& VideoStream::GetMetadata() const noexcept { return m_metadata; }
