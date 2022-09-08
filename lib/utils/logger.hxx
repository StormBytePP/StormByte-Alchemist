#pragma once

#include <fstream>
#include <filesystem>

namespace StormByte::VideoConvert::Utils {
	class Logger {
		public:
			enum LEVEL:unsigned short {
				LEVEL_DEBUG = 0,
				LEVEL_WARNING,
				LEVEL_INFO,
				LEVEL_ERROR,
				LEVEL_FATAL,
				LEVEL_MAX
			};
			Logger(const std::filesystem::path& logfile, LEVEL display_level);
			Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;
			~Logger();
			
			void message_part_begin(const LEVEL& level, const std::string& msg);
			void message_part_continue(const LEVEL& level, const std::string& msg);
			void message_part_end(const LEVEL& level, const std::string& msg);
			void message_line(const LEVEL& level, const std::string& msg);
			void end_line(const LEVEL& level);
			

		private:
			std::ofstream m_logfile;
			LEVEL m_display_level;

			void timestamp(const LEVEL& log_level);
	};
}
