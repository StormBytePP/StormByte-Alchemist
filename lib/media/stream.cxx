#include "stream.hxx"

Alchemist::Media::Stream::Stream(unsigned short index):m_index(index) { }

unsigned short Alchemist::Media::Stream::get_index() const noexcept {
	return m_index;
}

const std::shared_ptr<Alchemist::Media::Codec::Base>& Alchemist::Media::Stream::get_codec() const noexcept {
	return m_codec;
}

void Alchemist::Media::Stream::set_codec(std::shared_ptr<Codec::Base> codec) noexcept {
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

const std::optional<std::string>& Alchemist::Media::Stream::get_title() const noexcept {
	return m_title;
}

void Alchemist::Media::Stream::set_title(const std::string& title) {
	m_title = title;
}

void Alchemist::Media::Stream::set_title(std::string&& title) noexcept {
	m_title = std::move(title);
}

const std::optional<std::string>& Alchemist::Media::Stream::get_bitrate() const noexcept {
	return m_bitrate;
}

void Alchemist::Media::Stream::set_bitrate(const std::string& bitrate) {
	m_bitrate = bitrate;
}

void Alchemist::Media::Stream::set_bitrate(std::string&& bitrate) noexcept {
	m_bitrate = std::move(bitrate);
}