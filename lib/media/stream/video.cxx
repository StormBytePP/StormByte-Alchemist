#include "video.hxx"

using namespace Alchemist::Media;

VideoStream::VideoStream(std::shared_ptr<VideoCodec> codec, const Metadata::Video& metadata):
Stream(codec), m_metadata(metadata) {}

VideoStream::VideoStream(std::shared_ptr<VideoCodec> codec, Metadata::Video&& metadata) noexcept:
Stream(codec), m_metadata(std::move(metadata)) {}

const Metadata::Video& VideoStream::GetMetadata() const noexcept { return m_metadata; }
