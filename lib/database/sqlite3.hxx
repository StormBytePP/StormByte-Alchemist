#pragma once

#include <filesystem>
#include <map>
#include <sqlite3.h>

namespace Alchemist::Database {
	class SQLite3 {
		public:
			SQLite3(const std::filesystem::path& dbfile);
			SQLite3(const SQLite3& db) 				= delete;
			SQLite3(SQLite3&& db) 					= default;
			SQLite3& operator=(const SQLite3& db) 	= delete;
			SQLite3& operator=(SQLite3&& db) 		= default;
			~SQLite3();

		private:
			static const std::string DATABASE_CREATE_SQL;
			static const std::map<std::string, std::string> DATABASE_PREPARED_SENTENCES;

			sqlite3* m_database;
			std::map<std::string, sqlite3_stmt*> m_prepared;

			/* Database internals */
			bool check_database();
			void init_database();
			void enable_foreign_keys();
			void prepare_sentences();
			void throw_error(char* err_msg);
			void reset_stmt(sqlite3_stmt*);
			void begin_transaction();
			void begin_exclusive_transaction();
			void commit_transaction();
			void rollback_transaction();
	};
}