#include "unknown.hxx"

Alchemist::Media::Container::Unknown::Unknown(std::string&& ext):Base(Container::UNKNOWN, ext) { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::Unknown::get_supported_codecs() const {
	return {
	};
}