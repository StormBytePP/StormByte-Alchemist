#pragma once

#include <fstream>
#include <filesystem>

namespace StormByte::VideoConvert {
	class Logger {
		public:
			Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;
			~Logger();
			
			static Logger& getInstance();
			void message(const std::string& msg);

		private:
			Logger();

			std::ofstream m_logfile;
			static const std::filesystem::path DEFAULT_LOGFILE;
	};
}
