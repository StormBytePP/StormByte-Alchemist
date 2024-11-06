#include <Alchemy/database/alchemy.hxx>
#include <Alchemy/database/file.hxx>
#include <Alchemy/media/file.hxx>
#include <Alchemy/media/audio/stream.hxx>
#include <Alchemy/media/video/stream.hxx>
#include <Alchemy/media/subtitle/stream.hxx>
#include "generated/database_create.hxx" // Autogenerated by CMake

#include <StormByte/database/sqlite/exception.hxx>
#include <StormByte/database/sqlite/prepared_stmt.hxx>
#include <StormByte/database/sqlite/result.hxx>

using namespace Alchemist::Database;
using namespace StormByte::Database;

const std::string Alchemy::DATABASE_CREATE_QUERY = ALCHEMY_DATABASE_CREATE_QUERY;
const std::map<std::string, std::string> Alchemy::DATABASE_PREPARED_SENTENCES = {
	{ "new_film",					"INSERT INTO films(in_file, in_size, out_file, priority) VALUES (?, ?, ?, ?) RETURNING film_id"	},
	{ "new_stream",					"INSERT INTO streams(film_id, stream_id, stream_type, title, lang) VALUES (?, ?, ?, ?, ?)"		},
	{ "new_meta_audio",				"INSERT INTO stream_metadata_audio(film_id, stream_id, codec, sample_rate, channels) VALUES (?, ?, ?, ?, ?)"					},
	{ "new_meta_video",				"INSERT INTO stream_metadata_video(film_id, stream_id, frames, codec) VALUES (?, ?, ?, ?)"		},
	{ "new_meta_video_res",			"INSERT INTO stream_metadata_video_resolution(film_id, stream_id, width, height) VALUES (?, ?, ?, ?)" },
	{ "new_meta_video_color",		"INSERT INTO stream_metadata_video_color(film_id, stream_id, prim, matrix, transfer, pix_fmt) VALUES (?, ?, ?, ?, ?, ?)" },
	{ "new_meta_video_hdr10",		"INSERT INTO stream_metadata_video_hdr10(film_id, stream_id, red_x, red_y, green_x, green_y, blue_x, blue_y, white_x, white_y, lum_min, lum_max, light_max, light_avg, has_plus) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" },
	{ "new_meta_subtitle",			"INSERT INTO stream_metadata_video_subtitle(film_id, stream_id, encoding) VALUES (?, ?, ?)"		},
	{ "clear_statuses",				"UPDATE films SET active = FALSE, failed = FALSE"											},
	{ "get_film_data",				"SELECT in_file, in_size, out_file, out_size, encode_time, priority, active, enabled, failed FROM films WHERE film_id = ?" },
	{ "get_film_streams",			"SELECT stream_id, stream_type, title, lang FROM streams WHERE film_id = ?"						},
	{ "get_film_meta_audio",		"SELECT codec, sample_rate, channels FROM stream_metadata_audio WHERE film_id = ? AND stream_id = ?"					},
	{ "get_film_meta_video",		"SELECT frames, codec FROM stream_metadata_video WHERE film_id = ? AND stream_id = ?"					},
	{ "get_film_meta_video_res",	"SELECT width, height FROM stream_metadata_video_resolution WHERE film_id = ? AND stream_id = ?"},
	{ "get_film_meta_video_color",	"SELECT prim, matrix, transfer, pix_fmt FROM stream_metadata_video_color WHERE film_id = ? AND stream_id = ?"	},
	{ "get_film_meta_video_hdr10",	"SELECT red_x, red_y, green_x, green_y, blue_x, blue_y, white_x, white_y, lum_min, lum_max, light_max, light_avg, has_plus FROM stream_metadata_video_hdr10 WHERE film_id = ? AND stream_id = ?" },
	{ "get_film_meta_subtitle",		"SELECT encoding FROM stream_metadata_video_subtitle WHERE film_id = ? AND stream_id = ?" },
	{ "get_film_id_for_encode",		"SELECT film_id FROM films WHERE enabled = TRUE AND active = FALSE AND out_size IS NULL ORDER BY priority ASC LIMIT 1" },
	{ "mark_film_as_active",		"UPDATE films SET active = TRUE WHERE film_id = ?" },
	{ "mark_film_as_failed",		"UPDATE films SET active = FALSE, failed = TRUE WHERE film_id = ?" },
	{ "complete_film",				"UPDATE films SET active = FALSE, failed = FALSE, out_size = ?, encode_time = ? WHERE film_id = ?" },
	{ "get_all_films",				"SELECT film_id FROM films ORDER BY film_id DESC" }
};

Alchemy::Alchemy(const std::filesystem::path& dbfile):SQLite::SQLite3(dbfile) {
	init_database();
}

//Alchemy::~Alchemy() noexcept {}

void Alchemy::ClearStatuses() {
	begin_exclusive_transaction();

	std::shared_ptr<SQLite::PreparedSTMT> stmt = get_prepared("clear_statuses");
	stmt->Step();
	stmt->Reset();

	commit_transaction();
}

int Alchemy::SaveFilm(const std::filesystem::path& source_file, const Media::File& outfile, const int& prio) {
	begin_exclusive_transaction();

	/* Insert Film */
	std::shared_ptr<SQLite::PreparedSTMT> stmt = get_prepared("new_film");
	stmt->Bind(0, source_file.string());
	stmt->Bind(1, outfile.GetSize());
	stmt->Bind(2, outfile.GetFileName());
	stmt->Bind(3, prio);

	int film_id = stmt->Step()->At(0)->Value<int>();
	stmt->Reset();

	for (auto it = outfile.GetStreams().begin(); it != outfile.GetStreams().end(); it++) {
		/* Stream basic */
		stmt = get_prepared("new_stream");
		const int stream_id = (*it)->GetIndex();
		const Media::Type stream_type = (*it)->GetType();
		stmt->Bind(0, film_id);
		stmt->Bind(1, stream_id);
		stmt->Bind(2, static_cast<int>(stream_type));

		if ((*it)->GetTitle())
			stmt->Bind(4, (*it)->GetTitle().value());
		else
			stmt->Bind(4, nullptr);
		if ((*it)->GetLanguage())
			stmt->Bind(5, (*it)->GetLanguage().value());
		else
			stmt->Bind(5, nullptr);

		stmt->Step();
		stmt->Reset();

		switch(stream_type) {
			case Media::Type::Audio: {
				std::shared_ptr<Media::Audio::Stream> audio_stream = std::dynamic_pointer_cast<Media::Audio::Stream>(*it);
				std::shared_ptr<Media::Audio::Metadata> audio_metadata = std::dynamic_pointer_cast<Media::Audio::Metadata>(audio_stream->GetMetadata());
				stmt = get_prepared("new_meta_audio");
				stmt->Bind(0, film_id);
				stmt->Bind(1, stream_id);
				stmt->Bind(2, audio_stream->GetCodec()->GetEncoderName());
				stmt->Bind(3, audio_metadata->GetSampleRate());
				stmt->Bind(4, audio_metadata->GetChannels());
				stmt->Step();
				stmt->Reset();
				break;
			}
			case Media::Type::Video: {
				std::shared_ptr<Media::Video::Stream> video_stream = std::dynamic_pointer_cast<Media::Video::Stream>(*it);
				std::shared_ptr<Media::Video::Metadata> video_metadata = std::dynamic_pointer_cast<Media::Video::Metadata>(video_stream->GetMetadata());
				if (video_metadata->GetFrames()) {
					stmt = get_prepared("new_meta_video");
					stmt->Bind(0, film_id);
					stmt->Bind(1, stream_id);
					stmt->Bind(2, video_metadata->GetFrames().value());
					stmt->Bind(3, video_stream->GetCodec()->GetEncoderName());
					stmt->Step();
					stmt->Reset();
				}
				if (video_metadata->GetResolution()) {
					stmt = get_prepared("new_meta_video_res");
					stmt->Bind(0, film_id);
					stmt->Bind(1, stream_id);
					stmt->Bind(2, video_metadata->GetResolution()->GetWidth());
					stmt->Bind(3, video_metadata->GetResolution()->GetHeight());
					stmt->Step();
					stmt->Reset();
				}
				if (video_metadata->GetColor()) {
					stmt = get_prepared("new_meta_video_color");
					stmt->Bind(0, film_id);
					stmt->Bind(1, stream_id);
					stmt->Bind(2, *video_metadata->GetColor()->GetPrimaries());
					stmt->Bind(3, *video_metadata->GetColor()->GetMatrix());
					stmt->Bind(4, *video_metadata->GetColor()->GetTransfer());
					stmt->Bind(5, *video_metadata->GetColor()->GetPixelFormat());
					stmt->Step();
					stmt->Reset();
				}
				if (video_metadata->GetHDR10()) {
					stmt = get_prepared("new_meta_video_hdr10");
					stmt->Bind(0, film_id);
					stmt->Bind(1, stream_id);
					stmt->Bind(2, video_metadata->GetHDR10()->GetRedPoint().first);
					stmt->Bind(3, video_metadata->GetHDR10()->GetRedPoint().second);
					stmt->Bind(4, video_metadata->GetHDR10()->GetGreenPoint().first);
					stmt->Bind(5, video_metadata->GetHDR10()->GetGreenPoint().second);
					stmt->Bind(6, video_metadata->GetHDR10()->GetBluePoint().first);
					stmt->Bind(7, video_metadata->GetHDR10()->GetBluePoint().second);
					stmt->Bind(8, video_metadata->GetHDR10()->GetWhitePoint().first);
					stmt->Bind(9, video_metadata->GetHDR10()->GetWhitePoint().second);
					stmt->Bind(10, video_metadata->GetHDR10()->GetLuminance().first);
					stmt->Bind(11, video_metadata->GetHDR10()->GetLuminance().second);
					if (video_metadata->GetHDR10()->GetLightLevel()) {
						stmt->Bind(12, video_metadata->GetHDR10()->GetLightLevel()->first);
						stmt->Bind(13, video_metadata->GetHDR10()->GetLightLevel()->second);
					}
					else {
						stmt->Bind(12, nullptr);
						stmt->Bind(13, nullptr);
					}
					stmt->Step();
					stmt->Reset();
				}
				break;
			}
			case Media::Type::Subtitle: {
				std::shared_ptr<Media::Subtitle::Stream> subtitle_stream = std::dynamic_pointer_cast<Media::Subtitle::Stream>(*it);
				std::shared_ptr<Media::Subtitle::Metadata> subtitle_metadata = std::dynamic_pointer_cast<Media::Subtitle::Metadata>(subtitle_stream->GetMetadata());
				stmt = get_prepared("new_meta_subtitle");
				stmt->Bind(0, film_id);
				stmt->Bind(1, stream_id);
				stmt->Bind(2, subtitle_metadata->GetString());
				stmt->Step();
				stmt->Reset();
				break;
			}
			default:
				break;
		}
	}

	commit_transaction();
	return film_id;
}

std::shared_ptr<File> Alchemy::GetFilm(const unsigned int& film_id) {
	std::shared_ptr<File> film;
	std::shared_ptr<SQLite::PreparedSTMT> stmt = get_prepared("get_film_data");
	stmt->Bind(0, film_id);
	std::shared_ptr<SQLite::Row> row = stmt->Step();
	if (row) {
		film = std::make_shared<File>();
		film->SetInFile(row->At("in_file")->Value<std::string>());
		film->SetInSize(row->At("in_size")->Value<int64_t>());
		film->SetOutFile(row->At("out_file")->Value<std::string>());
		if (!row->At("out_size")->IsNull())
			film->SetOutSize(row->At("out_size")->Value<int64_t>());
		if (!row->At("encode_time")->IsNull())
			film->SetEncodeTime(row->At("encode_time")->Value<int>());
		film->SetPriority(row->At("priority")->Value<int>());
		film->SetActiveStatus(row->At("active")->Value<bool>());
		film->SetEnabledStatus(row->At("enabled")->Value<bool>());
		film->SetFailedStatus(row->At("failed")->Value<bool>());
		stmt->Reset();

		/* Streams */
		stmt = get_prepared("get_film_streams");
		stmt->Bind(0, film_id);
		while (std::shared_ptr<SQLite::Row> stream_row = stmt->Step()) {
			const int stream_index = stream_row->At("stream_id")->Value<int>();
			const std::string stream_type = stream_row->At("stream_type")->Value<std::string>();
			const std::string stream_title = stream_row->At("title")->IsNull() ? "" : row->At("title")->Value<std::string>();
			const std::string stream_language = stream_row->At("language")->IsNull() ? "" : row->At("language")->Value<std::string>();
			
			if (stream_type == "a") {
				std::shared_ptr<Media::Audio::Stream> stream = std::make_shared<Media::Audio::Stream>(stream_index);
				std::shared_ptr<SQLite::PreparedSTMT> stmt_audio = get_prepared("get_film_meta_audio");
				stmt_audio->Bind(0, film_id);
				stmt_audio->Bind(1, stream_index);
				std::shared_ptr<SQLite::Row> audio_row;
				if ((audio_row = stmt_audio->Step())) {
					const std::string codec = audio_row->At("codec")->Value<std::string>();
					stream->SetCodec(Media::Audio::Codec::All.at(codec));
					stream->SetMetadata(
						{
							audio_row->At("sample_rate")->Value<int>(),
							audio_row->At("channels")->Value<int>()
						}
					);
					stmt_audio->Reset();
					film->AddStream(stream);
				}
			}
			else if (stream_type == "v") {
				std::shared_ptr<Media::Video::Stream> stream = std::make_shared<Media::Video::Stream>(stream_index);
				Media::Video::Metadata metadata;
				std::shared_ptr<SQLite::PreparedSTMT> stmt_video = get_prepared("get_film_meta_video");
				stmt_video->Bind(0, film_id);
				stmt_video->Bind(1, stream_index);
				std::shared_ptr<SQLite::Row> video_row;
				if ((video_row = stmt_video->Step())) {
					metadata.SetFrames(video_row->At("frames")->Value<int>());
					stream->SetCodec(Media::Video::Codec::All.at(video_row->At("codec")->Value<std::string>()));
				}
				stmt_video->Reset();
				stmt_video = get_prepared("get_film_meta_video_res");
				stmt_video->Bind(0, film_id);
				stmt_video->Bind(1, stream_index);
				if ((video_row = stmt_video->Step())) {
					metadata.SetResolution(
						{
							video_row->At("width")->Value<int>(),
							video_row->At("height")->Value<int>()
						}
					);
				}
				stmt_video->Reset();
				stmt_video = get_prepared("get_film_meta_video_color");
				stmt_video->Bind(0, film_id);
				stmt_video->Bind(1, stream_index);
				if ((video_row = stmt_video->Step())) {
					metadata.SetColor(
						{
							video_row->At("prim")->Value<std::string>(),
							video_row->At("matrix")->Value<std::string>(),
							video_row->At("transfer")->Value<std::string>(),
							video_row->At("pix_fmt")->Value<std::string>()
						}
					);
				}
				stmt_video->Reset();
				stmt_video = get_prepared("get_film_meta_video_hdr10");
				stmt_video->Bind(0, film_id);
				stmt_video->Bind(1, stream_index);
				if ((video_row = stmt_video->Step())) {
					Media::Video::HDR10 hdr10(
						{
							{ video_row->At("red_x")->Value<int>(),		video_row->At("red_y")->Value<int>() },
							{ video_row->At("green_x")->Value<int>(),	video_row->At("green_y")->Value<int>() },
							{ video_row->At("blue_x")->Value<int>(),	video_row->At("blue_y")->Value<int>() },
							{ video_row->At("white_x")->Value<int>(),	video_row->At("white_y")->Value<int>() },
							{ video_row->At("lum_min")->Value<int>(),	video_row->At("lum_max")->Value<int>() }
						}
					);
					if (!video_row->At("light_max")->IsNull() && !video_row->At("light_avg")->IsNull())
						hdr10.SetLightLevel(
							{
								video_row->At("light_max")->Value<int>(), video_row->At("light_avg")->Value<int>()
							}
						);
					if (video_row->At("has_plus")->Value<bool>())
						hdr10.SetPlusFile("yes"); // File will be corrected by converter
					metadata.SetHDR10(std::move(hdr10));
				}
				stmt_video->Reset();
				stream->SetMetadata(std::move(metadata));
				film->AddStream(stream);
			}
			else if (stream_type == "s") {
				std::shared_ptr<Media::Subtitle::Stream> stream = std::make_shared<Media::Subtitle::Stream>(stream_index);
				std::shared_ptr<SQLite::PreparedSTMT> stmt_subtitle = get_prepared("get_film_meta_subtitle");
				stmt_subtitle->Bind(0, film_id);
				stmt_subtitle->Bind(1, stream_index);
				std::shared_ptr<SQLite::Row> subtitle_row;
				if ((subtitle_row = stmt_subtitle->Step())) {
					stream->SetMetadata({ subtitle_row->At("encoding")->Value<std::string>() });
				}
				stmt_subtitle->Reset();
				film->AddStream(stream);
			}
		}
		stmt->Reset();
	}
	return film;
}

std::shared_ptr<File> Alchemy::GetFilm() {
	begin_exclusive_transaction();

	std::shared_ptr<SQLite::PreparedSTMT> stmt = get_prepared("get_film_id_for_encode");
	std::shared_ptr<File> film;
	if (std::shared_ptr<SQLite::Row> row = stmt->Step()) {
		int film_id = row->At("film_id")->Value<int>();
		film = GetFilm(film_id);
		stmt->Reset();

		stmt = get_prepared("mark_film_as_active");
		stmt->Bind(0, film_id);
		stmt->Step();
	}
	stmt->Reset();

	commit_transaction();
	return film;
}

void Alchemy::SetAsFailed(const File& film) {
	begin_exclusive_transaction();

	std::shared_ptr<SQLite::PreparedSTMT> stmt = get_prepared("mark_film_as_failed");
	stmt->Bind(0, film.GetFilmID());
	stmt->Step();
	stmt->Reset();

	commit_transaction();
}

void Alchemy::SetAsCompleted(const File& film) {
	begin_exclusive_transaction();

	std::shared_ptr<SQLite::PreparedSTMT> stmt = get_prepared("complete_film");
	stmt->Bind(0, *film.GetOutSize());
	stmt->Bind(1, *film.GetEncodeTime());
	stmt->Bind(2, film.GetFilmID());
	stmt->Step();
	stmt->Reset();

	commit_transaction();
}

std::list<std::shared_ptr<File>> Alchemy::GetAllFilms() {
	begin_exclusive_transaction();

	std::shared_ptr<SQLite::PreparedSTMT> stmt = get_prepared("get_all_films");
	std::list<std::shared_ptr<File>> films;
	while (std::shared_ptr<SQLite::Row> row = stmt->Step())
		films.push_back(GetFilm(row->At("film_id")->Value<int>()));
	stmt->Reset();

	commit_transaction();
	return films;
}

void Alchemy::post_init_action() noexcept {
	try {
		silent_query("SELECT * FROM films");
	}
	catch(const SQLite::QueryError&) {
		silent_query(DATABASE_CREATE_QUERY); // It should NOT fail
	}
	for (auto it = DATABASE_PREPARED_SENTENCES.begin(); it != DATABASE_PREPARED_SENTENCES.end(); it++)
		prepare_sentence(it->first, it->second);
}

