#include "base.hxx"

#include <libconfig.h++>

using namespace StormByte::VideoConvert;

Configuration::Base::Base(const std::list<std::string>& mandatory_string, const std::list<std::string>& mandatory_int, const std::list<std::string>& optional_string, const std::list<std::string>& optional_int):m_mandatory_string_values(mandatory_string), m_mandatory_int_values(mandatory_int), m_optional_string_values(optional_string), m_optional_int_values(optional_int) {}

Configuration::Base& Configuration::Base::operator=(const Base& b) {
	if (this != &b) {
		m_values_string = b.m_values_string;
		m_values_int = b.m_values_int;
		m_errors = b.m_errors;
	}
	return *this;
}

Configuration::Base& Configuration::Base::operator=(Base&& b) noexcept {
	if (this != &b) {
		m_values_string = std::move(b.m_values_string);
		m_values_int = std::move(b.m_values_int);
		m_errors = std::move(b.m_errors);
	}
	return *this;
}

void Configuration::Base::parse(const Types::path_t& file) noexcept {
	m_errors.clear();
	m_values_int.clear();
	m_values_string.clear();

	libconfig::Config cfg;
	std::string config_file = file;
	try {
    	cfg.readFile(config_file.c_str());
	}
	catch(const libconfig::FileIOException &fioex) {
		m_errors.emplace("read error", "Can not open configuration file " + config_file);
	}
	catch(const libconfig::ParseException &pex) {
		m_errors.emplace("parse error", std::string(pex.getFile()) + " at line " + std::to_string(pex.getLine()) + " " + pex.getError());
	}
	
	if (m_errors.empty()) {
		for (std::string item: m_mandatory_string_values ) {
			if (cfg.exists(item))
				set_string_value(item, std::move(cfg.lookup(item)));
			else
				m_errors.emplace(item, "Mandatory item missing in config");
		}

		for (std::string item: m_mandatory_int_values ) {
			if (cfg.exists(item)) {
				int value;
				if (cfg.lookupValue(item, value))
					set_int_value(item, std::move(value));
				else
					m_errors.emplace(item, "Value is not an integer");
			}
		}

		for (std::string item: m_optional_string_values) {
			if (cfg.exists(item))
				set_string_value(item, std::move(cfg.lookup(item)));
		}

		for (std::string item: m_optional_int_values) {
			if (cfg.exists(item)) {
				int value;
				if (cfg.lookupValue(item, value))
					set_int_value(item, std::move(value));
				else
					m_errors.emplace(item, "Value is not an integer");
			}
		}
	}
}

void Configuration::Base::merge(const Base& config) {
	for (auto it = config.m_values_string.begin(); it != config.m_values_string.end(); it++) {
		set_string_value(it->first, it->second);
	}

	for (auto it = config.m_values_int.begin(); it != config.m_values_int.end(); it++) {
		set_int_value(it->first, it->second);
	}
}

void Configuration::Base::merge(Base&& config) noexcept {
	for (auto it = std::make_move_iterator(config.m_values_string.begin()); it != std::make_move_iterator(config.m_values_string.end()); it++) {
		m_errors.erase((*it).first);
		m_values_string.emplace(std::move(*it));
	}

	for (auto it = std::make_move_iterator(config.m_values_int.begin()); it != std::make_move_iterator(config.m_values_int.end()); it++) {
		m_errors.erase((*it).first);
		m_values_int.emplace(std::move(*it));
	}
}

bool Configuration::Base::have_all_mandatory_values() const {
	bool continue_search = true;

	for (auto it = m_mandatory_string_values.begin(); it != m_mandatory_string_values.end() && continue_search; it++)
		continue_search = m_values_string.contains(*it);

	for (auto it = m_mandatory_int_values.begin(); it != m_mandatory_int_values.end() && continue_search; it++)
		continue_search = m_values_int.contains(*it);

	return continue_search;
}
