#pragma once

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
#include "utils/logger.hxx"

#include <filesystem>
#include <vector>

namespace StormByte::VideoConvert {
	class FFmpeg {
		public:
			FFmpeg(const unsigned int& film_id, const std::filesystem::path& input_file, const std::optional<Database::Data::film::group>& group = std::optional<Database::Data::film::group>());
			FFmpeg(unsigned int&& film_id, std::filesystem::path&& input_file, std::optional<Database::Data::film::group>&& group = std::optional<Database::Data::film::group>());
			FFmpeg(const FFmpeg& ffmpeg) = default;
			FFmpeg(FFmpeg&& ffmpeg) noexcept = default;
			FFmpeg& operator=(const FFmpeg& ffmpeg) = default;
			FFmpeg& operator=(FFmpeg&& ffmpeg) noexcept = default;
			~FFmpeg() = default;

			void add_stream(const Stream::Base&);

			/* Getters */
			inline unsigned int get_film_id() const { return m_film_id; }
			std::optional<Database::Data::film::group> get_group() const { return m_group; }
			inline bool is_empty() const { return m_streams.empty(); }
			inline std::filesystem::path get_input_file() const { return m_input_file; }
			inline std::filesystem::path get_output_file() const { auto result = m_input_file; return result.replace_extension(m_container); }
			inline const auto& get_streams() const { return m_streams; }

		private:
			unsigned int m_film_id;
			std::filesystem::path m_input_file;
			std::optional<Database::Data::film::group> m_group;
			std::filesystem::path m_container; // For future
			std::list<std::shared_ptr<StormByte::VideoConvert::Stream::Base>> m_streams;
	};
}
