#pragma once

#include <filesystem>
#include <vector>

/* For convenience, all usable codecs are included here */
#include "stream/video/hevc.hxx"
#include "stream/video/copy.hxx"
#include "stream/audio/aac.hxx"
#include "stream/audio/fdk_aac.hxx"
#include "stream/audio/ac3.hxx"
#include "stream/audio/eac3.hxx"
#include "stream/audio/opus.hxx"
#include "stream/audio/copy.hxx"
#include "stream/subtitle/copy.hxx"

namespace StormByte::VideoConvert {
	class FFmpeg {
		public:
			FFmpeg(unsigned int film_id, const std::filesystem::path& in, const std::filesystem::path& out);
			FFmpeg(const FFmpeg& ffmpeg);
			FFmpeg(FFmpeg&& ffmpeg) noexcept;
			FFmpeg& operator=(const FFmpeg& ffmpeg);
			FFmpeg& operator=(FFmpeg&& ffmpeg) noexcept;
			~FFmpeg() = default;

			void add_stream(const StormByte::VideoConvert::Stream::Base&);
			pid_t exec();
			inline bool is_empty() const { return m_streams.empty(); }
			inline auto get_input_file() const { return m_input_file; }
#ifdef DEBUG
			void debug() const;
#endif

		private:
			unsigned int m_film_id;
			std::string m_input_file, m_output_file;
			std::list<std::unique_ptr<StormByte::VideoConvert::Stream::Base>> m_streams;
			static const std::list<const char*> FFMPEG_INIT_OPTIONS;

			std::vector<std::string> parameters() const;
	};
}
