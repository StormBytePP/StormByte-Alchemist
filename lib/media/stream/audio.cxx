#include "audio.hxx"

using namespace Alchemist::Media;

AudioStream::AudioStream(std::unique_ptr<AudioCodec>&& codec, const Metadata::Audio& metadata):Stream(std::move(codec)), m_metadata(metadata) {}

AudioStream::AudioStream(std::unique_ptr<AudioCodec>&& codec, Metadata::Audio&& metadata) noexcept:Stream(std::move(codec)), m_metadata(std::move(metadata)) {}

const Metadata::Audio& AudioStream::GetMetadata() const noexcept { return m_metadata; }