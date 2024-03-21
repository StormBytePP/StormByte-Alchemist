#include "container.hxx"

Alchemist::Media::Container::Base::Base(const std::string& ext):m_extension(ext) { }

Alchemist::Media::Container::Base::Base(std::string&& ext):m_extension(std::move(ext)) { }

const std::string& Alchemist::Media::Container::Base::get_extension() const {
	return m_extension;
}

std::shared_ptr<Alchemist::Media::Container::Base> Alchemist::Media::Container::Instance(const Type&) {
	return nullptr;
}