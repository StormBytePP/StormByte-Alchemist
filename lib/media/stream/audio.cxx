#include "audio.hxx"

using namespace Alchemist::Media;

Audio::Audio(std::shared_ptr<Codec> codec, const Metadata::Audio& metadata):Stream(codec), m_metadata(metadata) {}

Audio::Audio(std::shared_ptr<Codec>&& codec, Metadata::Audio&& metadata):Stream(std::move(codec)), m_metadata(std::move(metadata)) {}

const Metadata::Audio& Audio::GetMetadata() const { return m_metadata; }
