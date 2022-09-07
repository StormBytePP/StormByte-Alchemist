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
			~SQLite3();
			SQLite3& operator=(const SQLite3& db) = delete;
			std::optional<FFmpeg> get_film_for_process(const std::filesystem::path& output_path);
			void set_film_id_as_processing(int film_id);

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
			Data::film get_film_basic_data(int film_id);
			std::list<Data::stream> get_film_streams(int film_id);
			bool has_film_stream_HDR(const Data::stream& stream);
			Data::hdr get_film_stream_HDR(const Data::stream& stream);
			int insert_film(const Data::film& film);
			void insert_stream(const Data::stream& stream);
			void insert_HDR(const Data::stream& stream, const Data::hdr& hdr);
			
	};
}