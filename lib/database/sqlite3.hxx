#pragma once

#include <filesystem>
#include <sqlite3.h>

namespace StormByte::VideoConvert::Database {
	class SQLite3 {
		public:
			SQLite3(const std::filesystem::path& dbfile);
			SQLite3(const SQLite3& db) = delete;
			~SQLite3();
			SQLite3& operator=(const SQLite3& db) = delete;

		private:
			sqlite3* m_database;
	};
}