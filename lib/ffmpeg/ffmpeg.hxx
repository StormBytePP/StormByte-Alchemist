#pragma once

#include <filesystem>
#include <vector>

/* For convenience, all usable codecs are included here */
#ifdef ENABLE_HEVC
#include "stream/video/hevc.hxx"
#endif
#ifdef ENABLE_AAC
#include "stream/audio/aac.hxx"
#endif
#ifdef ENABLE_FDKAAC
#include "stream/audio/fdk_aac.hxx"
#endif
#ifdef ENABLE_AC3
#include "stream/audio/ac3.hxx"
#endif
#ifdef ENABLE_EAC3
#include "stream/audio/eac3.hxx"
#endif
#ifdef ENABLE_OPUS
#include "stream/audio/opus.hxx"
#endif

#include "stream/video/copy.hxx"
#include "stream/audio/copy.hxx"
#include "stream/subtitle/copy.hxx"
#include "database/data.hxx"

namespace StormByte::VideoConvert::Utils { class Logger; }

namespace StormByte::VideoConvert {
	class FFmpeg {
		public:
			FFmpeg(unsigned int film_id, const std::filesystem::path& input_path, const std::filesystem::path& input_file, const std::filesystem::path& work_path, const std::filesystem::path& output_path);
			FFmpeg(const FFmpeg& ffmpeg) = default;
			FFmpeg(FFmpeg&& ffmpeg) noexcept = default;
			FFmpeg& operator=(const FFmpeg& ffmpeg) = default;
			FFmpeg& operator=(FFmpeg&& ffmpeg) noexcept = default;
			~FFmpeg() = default;

			void add_stream(const StormByte::VideoConvert::Stream::Base&);
			pid_t exec() const;

			/* Getters */
			inline unsigned int get_film_id() const { return m_film_id; }
			inline void set_group(std::optional<Database::Data::group> group) { m_group = group; }
			std::optional<Database::Data::group> get_group() const { return m_group; }
			inline bool is_empty() const { return m_streams.empty(); }
			inline auto get_input_file() const { return m_input_file; }
			std::filesystem::path get_full_input_file() const;
			std::filesystem::path get_full_output_path() const;
			std::filesystem::path get_full_output_file() const;
			std::filesystem::path get_full_work_path() const;
			std::filesystem::path get_full_work_file() const;

		private:
			unsigned int m_film_id;
			std::optional<Database::Data::group> m_group;
			std::filesystem::path m_input_path, m_input_file, m_work_path, m_output_path;
			std::list<std::unique_ptr<StormByte::VideoConvert::Stream::Base>> m_streams;
			static const std::list<const char*> FFMPEG_INIT_OPTIONS;

			std::vector<std::string> parameters() const;
	};
}
