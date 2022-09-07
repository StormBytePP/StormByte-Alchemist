#include <filesystem>
#include <string>

namespace StormByte::VideoConvert {
	class Application {
		public:
			Application();
			Application(const Application&) = delete;
			Application& operator=(const Application&) = delete;
			~Application();

			int run(int argc, char** argv) noexcept;

		private:
			bool m_daemon_mode;
			std::filesystem::path m_database_file, m_output_path;

			static const std::filesystem::path DEFAULT_CONFIG_FILE;
			static const std::string PROGRAM_NAME, PROGRAM_DESCRIPTION, PROGRAM_OWNER, PROGRAM_VERSION;
			enum status { CONTINUE = 0, HALT_OK, ERROR };

			bool init_from_config();
			status init_from_cli(int argc, char** argv);
			void header() const;
			void help() const;
			void version() const;
	};
}
