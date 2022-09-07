#pragma once

#include <fstream>
#include <filesystem>

namespace StormByte::VideoConvert {
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
			
			static Logger& getInstance();
			void message(const LEVEL& level, const std::string& msg);

		private:
			std::ofstream m_logfile;
			LEVEL m_display_level;
	};
}
