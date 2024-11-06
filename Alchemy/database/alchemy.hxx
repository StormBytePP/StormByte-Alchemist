#pragma once

#include <Alchemy/visibility.h>
#include <StormByte/database/sqlite/sqlite3.hxx>

#include <filesystem>
#include <list>
#include <map>

namespace Alchemist::Media { class File; }

namespace Alchemist::Database {
	class File;
	class ALCHEMY_PUBLIC Alchemy final: public StormByte::Database::SQLite::SQLite3 {
		public:
			Alchemy(const std::filesystem::path& dbfile);
			Alchemy(const Alchemy& db) 				= delete;
			Alchemy(Alchemy&& db) 					= default;
			Alchemy& operator=(const Alchemy& db) 	= delete;
			Alchemy& operator=(Alchemy&& db) 		= default;
			~Alchemy() noexcept override			= default;

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