#include "item.hxx"

Alchemist::Media::Item::~Item() noexcept { }

unsigned short Alchemist::Media::Item::get_attributes() const noexcept {
	return m_attrs;
}

bool Alchemist::Media::Item::has_attribute(const Attribute& attr) const noexcept {
	return (m_attrs & attr) == attr;
}
