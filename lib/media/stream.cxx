#include "stream.hxx"

std::shared_ptr<Alchemist::Media::Codec::Base> Alchemist::Media::Stream::get_codec() const noexcept {
	return m_codec;
}

void Alchemist::Media::Stream::set_codec(std::unique_ptr<Codec::Base> codec) noexcept {
	m_codec = std::move(codec);
}

const std::optional<std::string>& Alchemist::Media::Stream::get_language() const noexcept {
	return m_language;
}

void Alchemist::Media::Stream::set_language(const std::string& lang) {
	m_language = lang;
}

void Alchemist::Media::Stream::set_language(std::string&& lang) noexcept {
	m_language = std::move(lang);
}
