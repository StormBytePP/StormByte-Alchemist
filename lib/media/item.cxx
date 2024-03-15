#include "item.hxx"

Alchemist::Media::Item::~Item() { }

unsigned short Alchemist::Media::Item::get_attributes() const {
	return m_attrs;
}

bool Alchemist::Media::Item::has_attribute(const Attribute& attr) const {
	return (m_attrs & attr) == attr;
}
