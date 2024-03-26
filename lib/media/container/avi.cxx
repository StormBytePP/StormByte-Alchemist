#include "avi.hxx"

Alchemist::Media::Container::AVI::AVI():Base(Container::AVI, "avi", 2) {
	m_attrs = Attribute::OLD;
}
