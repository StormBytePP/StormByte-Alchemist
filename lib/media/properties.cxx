#include "media/properties.hxx"

void STVC::Media::Properties::set_language(const std::string& str) { m_language = str; }

void STVC::Media::Properties::set_language(std::string&& str) { m_language = std::move(str); }