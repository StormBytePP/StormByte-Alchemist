#include "sqlite3.hxx"
#include <stdexcept>

StormByte::VideoConvert::Database::SQLite3::SQLite3(const std::filesystem::path& dbfile) {
	if (sqlite3_open(dbfile.c_str(), &m_database))
		throw std::runtime_error(std::string("Can not open database file ") + dbfile.c_str());
}

StormByte::VideoConvert::Database::SQLite3::~SQLite3() {
	sqlite3_close(m_database);
}
