#include "subtitle.hxx"

using namespace Alchemist::Media::Metadata;

Subtitle::Subtitle(const std::string& encoding):m_encoding(encoding) {}

Subtitle::Subtitle(std::string&& encoding) noexcept:m_encoding(std::move(encoding)) {}

const std::string& Subtitle::GetEncoding() const noexcept { return m_encoding; }