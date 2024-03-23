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

const std::optional<unsigned int>& Alchemist::Media::Stream::get_frame_number() const noexcept {
	return m_frame_number;
}

void Alchemist::Media::Stream::set_frame_number(const unsigned int& frames) {
	m_frame_number = frames;
}

void Alchemist::Media::Stream::set_frame_number(unsigned int&& frames) noexcept {
	m_frame_number = std::move(frames);
}

const std::optional<unsigned long>& Alchemist::Media::Stream::get_bytes() const noexcept {
	return m_bytes;
}

void Alchemist::Media::Stream::set_bytes(const unsigned long& bytes) {
	m_bytes = bytes;
}

void Alchemist::Media::Stream::set_bytes(unsigned long&& bytes) noexcept {
	m_bytes = std::move(bytes);
}

const std::optional<std::string>& Alchemist::Media::Stream::get_duration() const noexcept {
	return m_duration;
}

void Alchemist::Media::Stream::set_duration(const std::string& duration) {
	m_duration = duration;
}

void Alchemist::Media::Stream::set_duration(std::string&& duration) noexcept {
	m_duration = std::move(duration);
}