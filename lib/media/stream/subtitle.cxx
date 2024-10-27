#include "subtitle.hxx"

using namespace Alchemist::Media;

SubtitleStream::SubtitleStream(std::shared_ptr<SubtitleCodec> codec, const Metadata::Subtitle& metadata):
Stream(codec), m_metadata(metadata) {}

SubtitleStream::SubtitleStream(std::shared_ptr<SubtitleCodec> codec, Metadata::Subtitle&& metadata) noexcept:
Stream(codec), m_metadata(std::move(metadata)) {}

const Metadata::Subtitle& SubtitleStream::GetMetadata() const noexcept { return m_metadata; }