#include "codec.hxx"

using namespace Alchemist::Media;

Codec::Codec(std::string&& name, std::string&& desc) noexcept:m_name(std::move(name)), m_description(std::move(desc)) {}

const std::string& Codec::GetName() const noexcept { return m_name; }

const std::string& Codec::GetDescription() const noexcept { return m_description; }