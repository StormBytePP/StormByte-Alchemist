#include "metadata.hxx"

using namespace Alchemist::Media::Subtitle;

Metadata::Metadata(const std::string& encoding):m_encoding(encoding) {}

Metadata::Metadata(std::string&& encoding) noexcept:m_encoding(std::move(encoding)) {}

const std::string& Metadata::GetEncoding() const noexcept { return m_encoding; }