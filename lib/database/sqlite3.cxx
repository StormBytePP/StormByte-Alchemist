#include "sqlite3.hxx"

#include <stdexcept>

using namespace StormByte::VideoConvert;

const std::string Database::SQLite3::DATABASE_CREATE_SQL =
	"CREATE TABLE groups("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"folder VARCHAR NOT NULL"
	");"
	"CREATE TABLE films("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"file VARCHAR NOT NULL,"
		"prio TINYINT,"
		"processing BOOL DEFAULT FALSE,"
		"unsupported BOOL DEFAULT FALSE,"
		"group_id INTEGER DEFAULT NULL,"
		"FOREIGN KEY(group_id) REFERENCES groups(id) ON DELETE CASCADE"
	");"
	"CREATE TABLE streams("
		"id INTEGER,"
        "film_id INTEGER,"
		"codec INTEGER NOT NULL,"
		"is_animation BOOL DEFAULT FALSE,"
        "max_rate VARCHAR DEFAULT NULL,"
        "bitrate VARCHAR DEFAULT NULL,"
        "PRIMARY KEY(id, film_id, codec),"
        "FOREIGN KEY(film_id) REFERENCES films(id) ON DELETE CASCADE"
	");"
	"CREATE TABLE stream_hdr("
		"film_id INTEGER,"
		"stream_id INTEGER,"
		"codec INTEGER,"
		"red_x INTEGER NOT NULL,"
		"red_y INTEGER NOT NULL,"
		"green_x INTEGER NOT NULL,"
		"green_y INTEGER NOT NULL,"
		"blue_x INTEGER NOT NULL,"
		"blue_y INTEGER NOT NULL,"
		"white_point_x INTEGER NOT NULL,"
		"white_point_y INTEGER NOT NULL,"
		"luminance_min INTEGER NOT NULL,"
		"luminance_max INTEGER NOT NULL,"
		"light_level_content INTEGER,"
		"light_level_average INTEGER,"
		"PRIMARY KEY (film_id, stream_id, codec),"
		"FOREIGN KEY (film_id, stream_id, codec) REFERENCES streams(id, film_id, codec) ON DELETE CASCADE"
	");";

const std::map<std::string, std::string> Database::SQLite3::DATABASE_PREPARED_SENTENCES = {
	{"getFilmIDForProcess", 		"SELECT id FROM films WHERE processing = FALSE AND unsupported = FALSE ORDER BY prio DESC LIMIT 1"},
	{"setProcessingStatusForFilm",	"UPDATE films SET processing = ? WHERE id = ?"},
	{"setUnsupportedStatusForFilm",	"UPDATE films SET unsupported = ? WHERE id = ?"},
	{"deleteFilmStreamHDR",			"DELETE FROM stream_hdr WHERE film_id = ?"},
	{"getFilmData",					"SELECT file, prio, processing, unsupported, group_id FROM films WHERE id = ?"},
	{"getFilmStreams",				"SELECT id, codec, is_animation, max_rate, bitrate FROM streams WHERE film_id = ?"},
	{"hasStreamHDR?",				"SELECT COUNT(*)>0 FROM stream_hdr WHERE film_id = ? AND stream_id = ? AND codec = ?"},
	{"getFilmStreamHDR",			"SELECT red_x, red_y, green_x, green_y, blue_x, blue_y, white_point_x, white_point_y, luminance_min, luminance_max, light_level_content, light_level_average FROM stream_hdr WHERE film_id = ? AND stream_id = ? AND codec = ?"},
	{"getGroupData",				"SELECT folder FROM groups WHERE id = ?"},
	{"insertFilm",					"INSERT INTO films(file, prio, group_id) VALUES (?, ?, ?) RETURNING id"},
	{"insertStream",				"INSERT INTO streams(id, film_id, codec, is_animation, max_rate, bitrate) VALUES (?, ?, ?, ?, ?, ?)"},
	{"insertHDR",					"INSERT INTO stream_hdr(film_id, stream_id, codec, red_x, red_y, green_x, green_y, blue_x, blue_y, white_point_x, white_point_y, luminance_min, luminance_max, light_level_content, light_level_average) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"},
	{"insertGroup",					"INSERT INTO groups(folder) VALUES (?) RETURNING id"},
	{"resetProcessingFilms",		"UPDATE films SET processing = FALSE, unsupported = FALSE"},
	{"deleteFilm",					"DELETE FROM films WHERE id = ?"},
	{"deleteFilmStream",			"DELETE FROM streams WHERE film_id = ?"},
	{"deleteFilmStreamHDR",			"DELETE FROM stream_hdr WHERE film_id = ?"},
	{"isFilmAlreadyInDatabase?",	"SELECT COUNT(*)>0 FROM films WHERE file = ?"},
	{"doGroupExist?",				"SELECT COUNT(*)>0 FROM groups WHERE folder = ?"},
	{"isGroupEmpty?",				"SELECT COUNT(*)=0 FROM films WHERE group_id = ?"},
	{"deleteGroup",					"DELETE FROM groups WHERE id = ?"}
};

Database::SQLite3::SQLite3(const std::filesystem::path& dbfile, std::shared_ptr<Utils::Logger> logger):m_logger(logger) {
	int rc = sqlite3_open(dbfile.c_str(), &m_database);

	if (rc != SQLITE_OK) {
		const std::string message = "Cannot open database " + dbfile.string() + ": " + std::string(sqlite3_errmsg(m_database));
		sqlite3_close(m_database); // Need to close database here as exception throwing will skip destructor
        throw std::runtime_error(message);
    }
	if (!check_database()) init_database();
	prepare_sentences();
	
}

Database::SQLite3::~SQLite3() {
	for (auto it = m_prepared.begin(); it != m_prepared.end(); it++) {
		sqlite3_finalize(it->second);
	}
	m_prepared.clear();
	sqlite3_close(m_database);
}

std::optional<FFmpeg> Database::SQLite3::get_film_for_process() {
	begin_exclusive_transaction();
	std::optional<FFmpeg> ffmpeg;
	std::optional<unsigned int> film_id = get_film_id_for_process();

	if (film_id) {
		std::optional<Data::film> film_data = get_film_data(*film_id);
		if (film_data) {
			FFmpeg film(*film_data->m_id, film_data->m_file, film_data->m_group);
			auto streams = get_film_streams(*film_data->m_id);
			std::list<Data::film::stream::codec> unsupported_codecs;

			for (auto it = streams.begin(); it != streams.end(); it++) {
				switch (it->m_codec) {
					case Data::film::stream::VIDEO_HEVC: {
						#ifdef ENABLE_HEVC
						auto codec = Stream::Video::HEVC(it->m_id);
						if (it->m_hdr) {
							codec.set_HDR(std::move(*it->m_hdr));
						}
						if (it->m_is_animation) codec.set_tune_animation();
						film.add_stream(codec);
						#else
						unsupported_codecs.push_back(it->m_codec);
						#endif
						break;
					}
					case Data::film::stream::VIDEO_COPY: {
						film.add_stream(Stream::Video::Copy(it->m_id));
						break;
					}
					case Data::film::stream::AUDIO_AAC: {
						#ifdef ENABLE_AAC
						film.add_stream(Stream::Audio::AAC(it->m_id));
						#else
						unsupported_codecs.push_back(it->m_codec);
						#endif
						break;
					}
					case Data::film::stream::AUDIO_FDKAAC: {
						#ifdef ENABLE_FDKAAC
						film.add_stream(Stream::Audio::FDKAAC(it->m_id));
						#else
						unsupported_codecs.push_back(it->m_codec);
						#endif
						break;
					}
					case Data::film::stream::AUDIO_AC3: {
						#ifdef ENABLE_AC3
						film.add_stream(Stream::Audio::AC3(it->m_id));
						#else
						unsupported_codecs.push_back(it->m_codec);
						#endif
						break;
					}
					case Data::film::stream::AUDIO_COPY: {
						film.add_stream(Stream::Audio::Copy(it->m_id));
						break;
					}
					case Data::film::stream::AUDIO_EAC3: {
						#ifdef ENABLE_EAC3
						film.add_stream(Stream::Audio::EAC3(it->m_id));
						#else
						unsupported_codecs.push_back(it->m_codec);
						#endif
						break;
					}
					case Data::film::stream::AUDIO_OPUS: {
						#ifdef ENABLE_OPUS
						film.add_stream(Stream::Audio::Opus(it->m_id));
						#else
						unsupported_codecs.push_back(it->m_codec);
						#endif
						break;
					}
					case Data::film::stream::SUBTITLE_COPY: {
						film.add_stream(Stream::Subtitle::Copy(it->m_id));
						break;
					}
					default: {
						unsupported_codecs.push_back(Data::film::stream::INVALID_CODEC);
						break;
					}
				}
			}

			// We now check if we have unsupported codecs
			if (unsupported_codecs.empty()) {
				if (m_logger) m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Marking file " + film.get_input_file().string() + " as processing");
				set_film_processing_status(film.get_film_id(), true);
				ffmpeg.emplace(std::move(film));
			}
			else {
				if (m_logger) m_logger->message_part_begin(Utils::Logger::LEVEL_ERROR, "The file " + film.get_input_file().string() + " has the following unsupported codecs: ");
				for (auto it = unsupported_codecs.begin(); it != unsupported_codecs.end(); it++) {
					if (m_logger) m_logger->message_part_continue(Utils::Logger::LEVEL_ERROR, Database::Data::film::stream::codec_string.at(*it) + ", ");
				}
				if (m_logger) m_logger->message_part_end(Utils::Logger::LEVEL_ERROR, "and therefore could NOT be converted!");
				if (m_logger) m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Marking file " + film.get_input_file().string() + " as unsupported");
				set_film_unsupported_status(film.get_film_id(), true);
			}
		}
	}
	commit_transaction();
	return ffmpeg;
}

void Database::SQLite3::finish_film_process(const FFmpeg& ffmpeg, const bool& status) {
	begin_exclusive_transaction();

	if (status)
		delete_film(ffmpeg.get_film_id());
	else
		set_film_unsupported_status(ffmpeg.get_film_id(), true);

	commit_transaction();
}

bool Database::SQLite3::check_database() {
	char* err_msg = NULL;
	int rc = sqlite3_exec(m_database, "SELECT * FROM films;", nullptr, nullptr, &err_msg);
	sqlite3_free(err_msg);
	return rc == SQLITE_OK;
}

void Database::SQLite3::init_database() {
	if (m_logger) m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Constructing database");
	char* err_msg = NULL;
	int rc = sqlite3_exec(m_database, DATABASE_CREATE_SQL.c_str(), nullptr, nullptr, &err_msg);
	if (rc != SQLITE_OK) throw_error(err_msg);
}

void Database::SQLite3::throw_error(char* err_msg) {
	const std::string message = "Error creating database: " + std::string(err_msg);
	sqlite3_free(err_msg);
	throw std::runtime_error(message);
}

void Database::SQLite3::reset_stmt(sqlite3_stmt* stmt) {
	sqlite3_clear_bindings(stmt);
	sqlite3_reset(stmt);
}

void Database::SQLite3::begin_transaction() {
	char* err_msg = nullptr;
	sqlite3_exec(m_database, "BEGIN TRANSACTION;", nullptr, nullptr, &err_msg);
	sqlite3_free(err_msg);
	if (m_logger) m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Database transaction started");
}

void Database::SQLite3::begin_exclusive_transaction() {
	char* err_msg = nullptr;
	sqlite3_exec(m_database, "BEGIN EXCLUSIVE TRANSACTION;", nullptr, nullptr, &err_msg);
	sqlite3_free(err_msg);
	if (m_logger) m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Database EXCLUSIVE transaction started");
}

void Database::SQLite3::commit_transaction() {
	char* err_msg = nullptr;
	sqlite3_exec(m_database, "COMMIT;", nullptr, nullptr, &err_msg);
	sqlite3_free(err_msg);
	if (m_logger) m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Database transaction commited");
}

void Database::SQLite3::rollback_transaction() {
	char* err_msg = nullptr;
	sqlite3_exec(m_database, "ROLLBACK;", nullptr, nullptr, &err_msg);
	sqlite3_free(err_msg);
	if (m_logger) m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Database transaction ABORTED");
}

void Database::SQLite3::prepare_sentences() {
	for (auto it = DATABASE_PREPARED_SENTENCES.begin(); it != DATABASE_PREPARED_SENTENCES.end(); it++) {
		m_prepared[it->first] = nullptr;
		sqlite3_prepare_v2( m_database, it->second.c_str(), it->second.length(), &m_prepared[it->first], nullptr);
		if (!m_prepared[it->first])
			throw std::runtime_error("Prepared sentence " + (it->first) + " can not be loaded!");
	}
}

std::optional<unsigned int> Database::SQLite3::get_film_id_for_process() {
	std::optional<unsigned int> result;
	auto stmt = m_prepared["getFilmIDForProcess"];
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		result = sqlite3_column_int(stmt, 0);
	}
	sqlite3_reset(stmt);
	return result;
}

void Database::SQLite3::set_film_processing_status(const unsigned int& film_id, const bool& status) {
	auto stmt = m_prepared["setProcessingStatusForFilm"];
	sqlite3_bind_int(stmt, 1, status);
	sqlite3_bind_int(stmt, 2, film_id);
	sqlite3_step(stmt);
	reset_stmt(stmt);
}

void Database::SQLite3::set_film_unsupported_status(const unsigned int& film_id, const bool& status) {
	auto stmt = m_prepared["setUnsupportedStatusForFilm"];
	sqlite3_bind_int(stmt, 1, status);
	sqlite3_bind_int(stmt, 2, film_id);
	sqlite3_step(stmt);
	reset_stmt(stmt);
}

std::optional<Database::Data::film> Database::SQLite3::get_film_data(const unsigned int& film_id) {
	std::optional<Data::film> result;
	auto stmt = m_prepared["getFilmData"];
	sqlite3_bind_int(stmt, 1, film_id);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		Data::film film;
		film.m_id			= film_id;
		film.m_file 		= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		film.m_priority		= static_cast<Data::film::priority>(sqlite3_column_int(stmt, 1));
		film.m_processing	= sqlite3_column_int(stmt, 2);
		film.m_unsupported	= sqlite3_column_int(stmt, 3);
		if (sqlite3_column_type(stmt, 4) != SQLITE_NULL)
			film.m_group	= get_group_data(sqlite3_column_int(stmt, 4));
		result.emplace(std::move(film));
	}
	reset_stmt(stmt);
	return result;
}

std::list<Database::Data::film::stream> Database::SQLite3::get_film_streams(const unsigned int& film_id) {
	std::list<Data::film::stream> result;
	auto stmt = m_prepared["getFilmStreams"];
	sqlite3_bind_int(stmt, 1, film_id);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		Data::film::stream stream;
		stream.m_id				= sqlite3_column_int(stmt, 0);
		stream.m_codec 			= static_cast<Data::film::stream::codec>(sqlite3_column_int(stmt, 1));
		stream.m_is_animation	= sqlite3_column_int(stmt, 2);
		if (sqlite3_column_type(stmt, 3) != SQLITE_NULL) stream.m_max_rate 	= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		if (sqlite3_column_type(stmt, 4) != SQLITE_NULL) stream.m_bitrate 	= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		set_film_stream_HDR(film_id, stream);
		result.push_back(std::move(stream));
	}
	reset_stmt(stmt);
	return result;
}

bool Database::SQLite3::has_film_stream_HDR(const unsigned int& film_id, const Data::film::stream& stream) {
	bool result = false;
	auto stmt = m_prepared["hasStreamHDR?"];
	sqlite3_bind_int(stmt, 1, film_id);
	sqlite3_bind_int(stmt, 2, stream.m_id);
	sqlite3_bind_int(stmt, 3, stream.m_codec);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		result = static_cast<bool>(sqlite3_column_int(stmt, 0));
	}
	reset_stmt(stmt);
	return result;
}

void Database::SQLite3::set_film_stream_HDR(const unsigned int& film_id, Data::film::stream& stream) {
	if (has_film_stream_HDR(film_id, stream)) {
		Data::film::stream::hdr result;
		auto stmt = m_prepared["getFilmStreamHDR"];
		sqlite3_bind_int(stmt, 1, film_id);
		sqlite3_bind_int(stmt, 2, stream.m_id);
		sqlite3_bind_int(stmt, 3, stream.m_codec);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			result.red_x			= sqlite3_column_int(stmt, 0);
			result.red_y			= sqlite3_column_int(stmt, 1);
			result.green_x			= sqlite3_column_int(stmt, 2);
			result.green_y			= sqlite3_column_int(stmt, 3);
			result.blue_x			= sqlite3_column_int(stmt, 4);
			result.blue_y			= sqlite3_column_int(stmt, 5);
			result.white_point_x	= sqlite3_column_int(stmt, 6);
			result.white_point_y	= sqlite3_column_int(stmt, 7);
			result.luminance_min	= sqlite3_column_int(stmt, 8);
			result.luminance_max	= sqlite3_column_int(stmt, 9);
			if (sqlite3_column_type(stmt, 10) != SQLITE_NULL && sqlite3_column_type(stmt, 11) != SQLITE_NULL)
				result.light_level = std::make_pair(sqlite3_column_int(stmt, 10), sqlite3_column_int(stmt, 10));
			
			stream.m_hdr.emplace(std::move(result));
		}
		reset_stmt(stmt);
	}
}

std::optional<Database::Data::film::group> Database::SQLite3::get_group_data(const unsigned int& group_id) {
	std::optional<Data::film::group> result;
	auto stmt = m_prepared["getGroupData"];
	sqlite3_bind_int(stmt, 1, group_id);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		Data::film::group group;
		group.id 		= group_id;
		group.folder	= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		result.emplace(std::move(group));
	}
	reset_stmt(stmt);
	return result;
}

std::optional<unsigned int> Database::SQLite3::insert_film(const Data::film& film) {
	std::optional<unsigned int> film_id;
	if (!is_film_in_database(film.m_file)) {
		auto stmt = m_prepared["insertFilm"];
		sqlite3_bind_text(stmt, 1, film.m_file.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 2, film.m_priority);
		if (film.m_group)
			sqlite3_bind_int(stmt, 3, film.m_group->id);
		else
			sqlite3_bind_null(stmt, 3);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			film_id = sqlite3_column_int(stmt, 0);

			// Now we insert all streams
			for (auto stream = film.m_streams.begin(); stream != film.m_streams.end(); stream++)
				insert_stream(*film_id, *stream);
		}
		reset_stmt(stmt);
	}
	return film_id;
}

bool Database::SQLite3::insert_films(const std::list<Data::film>& films) {
	bool continue_inserting = true;
	begin_exclusive_transaction();

	for (auto film = films.begin(); film != films.end() && continue_inserting; film++) {
		if (!insert_film(*film)) continue_inserting = false;
	}

	if (continue_inserting)
		commit_transaction();
	else
		rollback_transaction();

	return continue_inserting;
}

void Database::SQLite3::insert_stream(const unsigned int& film_id, const Data::film::stream& stream) {
	auto stmt = m_prepared["insertStream"];
	sqlite3_bind_int(stmt, 1, stream.m_id);
	sqlite3_bind_int(stmt, 2, film_id);
	sqlite3_bind_int(stmt, 3, stream.m_codec);
	sqlite3_bind_int(stmt, 4, stream.m_is_animation);
	if (stream.m_max_rate)
		sqlite3_bind_text(stmt, 5, stream.m_max_rate->c_str(), -1, SQLITE_STATIC);
	else
		sqlite3_bind_null(stmt, 5);
	if (stream.m_bitrate)
		sqlite3_bind_text(stmt, 6, stream.m_bitrate->c_str(), -1, SQLITE_STATIC);
	else
		sqlite3_bind_null(stmt, 6);
	sqlite3_step(stmt); // No result
	reset_stmt(stmt);

	insert_HDR(film_id, stream);
}

void Database::SQLite3::insert_HDR(const unsigned int& film_id, const Data::film::stream& stream) {
	if (stream.m_hdr) {
		auto stmt = m_prepared["insertHDR"];
		sqlite3_bind_int(stmt, 1, film_id);
		sqlite3_bind_int(stmt, 2, stream.m_id);
		sqlite3_bind_int(stmt, 3, stream.m_codec);
		sqlite3_bind_int(stmt, 4, stream.m_hdr->red_x);
		sqlite3_bind_int(stmt, 5, stream.m_hdr->red_y);
		sqlite3_bind_int(stmt, 6, stream.m_hdr->green_x);
		sqlite3_bind_int(stmt, 7, stream.m_hdr->green_y);
		sqlite3_bind_int(stmt, 8, stream.m_hdr->blue_x);
		sqlite3_bind_int(stmt, 9, stream.m_hdr->blue_y);
		sqlite3_bind_int(stmt, 10, stream.m_hdr->white_point_x);
		sqlite3_bind_int(stmt, 11, stream.m_hdr->white_point_y);
		sqlite3_bind_int(stmt, 12, stream.m_hdr->luminance_min);
		sqlite3_bind_int(stmt, 13, stream.m_hdr->luminance_max);
		if (stream.m_hdr->light_level) {
			sqlite3_bind_int(stmt, 14, stream.m_hdr->light_level->first);
			sqlite3_bind_int(stmt, 15, stream.m_hdr->light_level->second);
		}
		else {
			sqlite3_bind_null(stmt, 14);
			sqlite3_bind_null(stmt, 15);
		}	
		sqlite3_step(stmt); // No result
		reset_stmt(stmt);
	}
}

std::optional<Database::Data::film::group> Database::SQLite3::insert_group(const std::filesystem::path& folder) {
	std::optional<Database::Data::film::group> group;
	if (!is_group_in_database(folder)) {
		auto stmt = m_prepared["insertGroup"];
		sqlite3_bind_text(stmt, 1, folder.c_str(), -1, SQLITE_STATIC);
		if (sqlite3_step(stmt) == SQLITE_ROW)
			group = get_group_data(sqlite3_column_int(stmt, 0));
		reset_stmt(stmt);
	}
	return group;
}

void Database::SQLite3::reset_processing_films() {
	auto stmt = m_prepared["resetProcessingFilms"];
	sqlite3_step(stmt); // No result
	reset_stmt(stmt);
}

void Database::SQLite3::delete_film(const unsigned int& film_id) {
	auto stmt = m_prepared["deleteFilm"];
	sqlite3_bind_int(stmt, 1, film_id);
	sqlite3_step(stmt);
	reset_stmt(stmt);
	delete_film_stream(film_id);
	delete_film_stream_HDR(film_id);
}

void Database::SQLite3::delete_film_stream(const unsigned int& film_id) {
	auto stmt = m_prepared["deleteFilmStream"];
	sqlite3_bind_int(stmt, 1, film_id);
	sqlite3_step(stmt);
	reset_stmt(stmt);
}

void Database::SQLite3::delete_film_stream_HDR(const unsigned int& film_id) {
	auto stmt = m_prepared["deleteFilmStreamHDR"];
	sqlite3_bind_int(stmt, 1, film_id);
	sqlite3_step(stmt);
	reset_stmt(stmt);
}

void Database::SQLite3::delete_group(const Data::film::group& group) {
	auto stmt = m_prepared["deleteGroup"];
	sqlite3_bind_int(stmt, 1, group.id);
	sqlite3_step(stmt);
	reset_stmt(stmt);
}

bool Database::SQLite3::is_film_in_database(const std::filesystem::path& file) {
	bool result = false;
	auto stmt = m_prepared["isFilmAlreadyInDatabase?"];
	sqlite3_bind_text(stmt, 1, file.c_str(), -1, SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		result = static_cast<bool>(sqlite3_column_int(stmt, 0));
	}
	reset_stmt(stmt);
	return result;
}

bool Database::SQLite3::is_group_in_database(const std::filesystem::path& path) {
	bool result = false;
	auto stmt = m_prepared["doGroupExist?"];
	sqlite3_bind_text(stmt, 1, path.c_str(), -1, SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		result = sqlite3_column_int(stmt, 0);
	}
	reset_stmt(stmt);
	return result;
}

bool Database::SQLite3::is_group_empty(const Data::film::group& group) {
	bool result = false;
	auto stmt = m_prepared["isGroupEmpty?"];
	sqlite3_bind_int(stmt, 1, group.id);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		result = sqlite3_column_int(stmt, 0);
	}
	reset_stmt(stmt);
	return result;
}
