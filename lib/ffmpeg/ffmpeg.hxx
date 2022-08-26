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
			FFmpeg(const std::filesystem::path& in, const std::filesystem::path& out);
			FFmpeg(const FFmpeg& ffmpeg) = delete;
			FFmpeg(FFmpeg&& ffmpeg);
			FFmpeg& operator=(const FFmpeg& ffmpeg) = delete;
			~FFmpeg();

			void add_stream(const StormByte::VideoConvert::Stream::Base&);
			bool exec();
			inline bool is_empty() const { return m_streams.empty(); }
			void debug() const; // To be removed

		private:
			std::string m_input_file, m_output_file;
			std::list<StormByte::VideoConvert::Stream::Base*> m_streams;
			std::vector<char*> m_parameters;
			static const std::list<const char*> FFMPEG_INIT_OPTIONS;
			
			void clear_parameters();
			void prepare_parameters();
			static char* convert(const std::string& str);
	};
}
