#include "subtitle.hxx"

Alchemist::Media::Codec::Subtitle::Base::Base(const Codec::Type& codec_type):Codec::Base(codec_type) { }

Alchemist::Media::Codec::Subtitle::Base::Base(Codec::Type&& codec_type):Codec::Base(std::move(codec_type)) { }

Alchemist::Media::Codec::Subtitle::Base::~Base() noexcept { }

bool Alchemist::Media::Codec::Subtitle::Base::is_video() const noexcept { return false; }

bool Alchemist::Media::Codec::Subtitle::Base::is_audio() const noexcept { return false; }

bool Alchemist::Media::Codec::Subtitle::Base::is_image() const noexcept { return false; }

bool Alchemist::Media::Codec::Subtitle::Base::is_subtitle() const noexcept { return true; }

const std::string& Alchemist::Media::Codec::Subtitle::Base::get_name() const noexcept { return m_name; }

void Alchemist::Media::Codec::Subtitle::Base::set_name(const std::string& name) { m_name = name; }

void Alchemist::Media::Codec::Subtitle::Base::set_name(std::string&& name) { m_name = std::move(name); }

const std::string& Alchemist::Media::Codec::Subtitle::Base::get_long_name() const noexcept { return m_long_name; }

void Alchemist::Media::Codec::Subtitle::Base::set_long_name(const std::string& long_name) { m_long_name = long_name; }

void Alchemist::Media::Codec::Subtitle::Base::set_long_name(std::string&& long_name) { m_long_name = std::move(long_name); }