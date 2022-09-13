#pragma once

#include "data.hxx"
#include "ffmpeg/ffmpeg.hxx"
#include "utils/logger.hxx"

#include <filesystem>
#include <map>
#include <sqlite3.h>

namespace StormByte::VideoConvert::Database {
	class SQLite3 {
		public:
			SQLite3(const std::filesystem::path& dbfile, std::shared_ptr<Utils::Logger> logger = std::shared_ptr<Utils::Logger>());
			SQLite3(const SQLite3& db) = delete;
			SQLite3(SQLite3&& db) = delete;
			SQLite3& operator=(const SQLite3& db) = delete;
			SQLite3& operator=(SQLite3&& db) = delete;
			~SQLite3();

			/* Read data */
			inline bool is_film_in_database(const Data::film& film) { return is_film_in_database(film.m_file); }
			bool is_film_in_database(const std::filesystem::path& file);
			bool is_group_in_database(const std::filesystem::path& path);
			bool is_group_empty(const Data::film::group& group);

			/* Write data */
			std::optional<FFmpeg> get_film_for_process();
			void finish_film_process(const FFmpeg& ffmpeg, const bool& status);
			void reset_processing_films();
			std::optional<unsigned int> insert_film(const Data::film& film);
			bool insert_films(const std::list<Data::film>& films);
			std::optional<Data::film::group> insert_group(const std::filesystem::path& folder);
			void delete_group(const Data::film::group& group);

		private:
			sqlite3* m_database;
			std::map<std::string, sqlite3_stmt*> m_prepared;
			std::shared_ptr<Utils::Logger> m_logger;
			static const std::string DATABASE_CREATE_SQL;
			static const std::map<std::string, std::string> DATABASE_PREPARED_SENTENCES;

			/* Database internals */
			bool check_database();
			void init_database();
			void prepare_sentences();
			void throw_error(char* err_msg);
			void reset_stmt(sqlite3_stmt*);
			void begin_transaction();
			void begin_exclusive_transaction();
			void commit_transaction();
			void rollback_transaction();

			/* Data managing internal functions */
			std::optional<unsigned int> get_film_id_for_process();
			std::optional<Data::film> get_film_data(const unsigned int& film_id);
			std::optional<Data::film::group> get_group_data(const unsigned int& group_id);
			std::list<Data::film::stream> get_film_streams(const unsigned int& film_id);
			bool has_film_stream_HDR(const unsigned int& film_id, const Data::film::stream& stream);
			void set_film_stream_HDR(const unsigned int& film_id, Data::film::stream& stream);
			void insert_stream(const unsigned int& film_id, const Data::film::stream& stream);
			void insert_HDR(const unsigned int& film_id, const Data::film::stream& stream);
			void delete_film(const unsigned int& film_id);
			void delete_film_stream(const unsigned int& film_id);
			void delete_film_stream_HDR(const unsigned int& film_id);
			void set_film_processing_status(const unsigned int& film_id, const bool& status);
			void set_film_unsupported_status(const unsigned int& film_id, const bool& status);
	};
}