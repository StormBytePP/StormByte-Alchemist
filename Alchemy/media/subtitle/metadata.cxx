#include <Alchemy/media/subtitle/metadata.hxx>

using namespace Alchemy::Media::Subtitle;

Metadata::Metadata(const std::string& encoding):m_encoding(encoding) {}

Metadata::Metadata(std::string&& encoding) noexcept:m_encoding(std::move(encoding)) {}

std::string Metadata::GetString() const { return m_encoding; }