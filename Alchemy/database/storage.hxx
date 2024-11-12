#pragma once

#include <Alchemy/visibility.h>
#include <StormByte/database/sqlite/sqlite3.hxx>

#include <filesystem>
#include <list>
#include <map>

namespace Alchemy::Media { class File; }

namespace Alchemy::Database {
	class File;
	class ALCHEMY_PUBLIC Storage final: public StormByte::Database::SQLite::SQLite3 {
		public:
			Storage(const std::filesystem::path& dbfile);
			Storage(const Storage& db) 				= delete;
			Storage(Storage&& db) 					= default;
			Storage& operator=(const Storage& db) 	= delete;
			Storage& operator=(Storage&& db) 		= default;
			~Storage() noexcept override			= default;

			void 									ClearStatuses();
			int 									SaveFilm(const std::filesystem::path&, const Media::File&, const int&);
			std::shared_ptr<File> 					GetFilm(const unsigned int&);
			std::shared_ptr<File> 					GetFilm();
			void									SetAsFailed(const File&);
			void									SetAsCompleted(const File&);
			std::list<std::shared_ptr<File>>		GetAllFilms();

		private:
			static const std::string DATABASE_CREATE_QUERY;
			static const std::map<std::string, std::string> DATABASE_PREPARED_SENTENCES;

			/* Database internals */
			void post_init_action() noexcept override;
	};
}