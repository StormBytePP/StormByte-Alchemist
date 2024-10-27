#include "subtitle.hxx"

using namespace Alchemist::Media;

Subtitle::Subtitle(std::shared_ptr<Codec> codec, const Metadata::Subtitle& metadata):
Stream(std::move(codec)), m_metadata(metadata) {}

Subtitle::Subtitle(std::shared_ptr<Codec>&& codec, Metadata::Subtitle&& metadata) noexcept:
Stream(std::move(codec)), m_metadata(std::move(metadata)) {}

const Metadata::Subtitle& Subtitle::GetMetadata() const noexcept { return m_metadata; }