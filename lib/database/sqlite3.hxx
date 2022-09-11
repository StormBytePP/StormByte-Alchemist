#pragma once

#include "ffmpeg/ffmpeg.hxx"
#include "data.hxx"

#include <filesystem>
#include <map>
#include <sqlite3.h>

namespace StormByte::VideoConvert::Database {
	class SQLite3 {
		public:
			SQLite3(const std::filesystem::path& dbfile);
			SQLite3(const SQLite3& db) = delete;
			SQLite3(SQLite3&& db) = delete;
			SQLite3& operator=(const SQLite3& db) = delete;
			SQLite3& operator=(SQLite3&& db) = delete;
			~SQLite3();

			void begin_transaction();
			void commit_transaction();
			void rollback_transaction();

			std::optional<FFmpeg> get_film_for_process();
			void set_film_processing_status(int film_id, bool status);
			void set_film_unsupported_status(int film_id, bool status);
			void reset_processing_films();
			void delete_film(unsigned int film_id);
			void delete_group(unsigned int group_id);
			inline bool is_film_in_database(const Data::film& film) { return is_film_in_database(film.file); }
			bool is_film_in_database(const std::filesystem::path& file);
			bool is_group_in_database(const std::filesystem::path& path);
			bool is_group_empty(unsigned int& group_id);
			
			/* Insert data functions */
			std::optional<int> insert_film(const Data::film& film);
			void insert_stream(const Data::stream& stream);
			std::optional<Data::group> insert_group(const std::filesystem::path& folder);

		private:
			sqlite3* m_database;
			std::map<std::string, sqlite3_stmt*> m_prepared;
			static const std::string DATABASE_CREATE_SQL;
			static const std::map<std::string, std::string> DATABASE_PREPARED_SENTENCES;

			/* Database internals */
			bool check_database();
			void init_database();
			void prepare_sentences();
			void throw_error(char* err_msg);
			void reset_stmt(sqlite3_stmt*);

			/* Data managing internal functions */
			int get_film_id_for_process();
			Data::film get_film_data(int film_id);
			std::optional<Data::group> get_group_data(unsigned int group_id);
			std::list<Data::stream> get_film_streams(int film_id);
			bool has_film_stream_HDR(const Data::stream& stream);
			Data::hdr get_film_stream_HDR(const Data::stream& stream);
			void insert_HDR(const Data::stream& stream);
			void delete_film_stream(int film_id);
			void delete_film_stream_HDR(int film_id);
	};
}