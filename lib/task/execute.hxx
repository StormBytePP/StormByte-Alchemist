#pragma once

#include "base.hxx"

#include <filesystem>

namespace StormByte::VideoConvert::Task {
	class Execute: public Base {
		public:
			Execute(const std::filesystem::path& program);
			Execute(const Execute& execute);
			Execute(Execute&& execute) noexcept = default;
			Execute& operator=(const Execute& execute);
			Execute& operator=(Execute&& execute) noexcept = default;
			~Execute() noexcept;

			virtual STATUS run(std::shared_ptr<Configuration> config) noexcept override;

			inline std::optional<pid_t> get_worker() const { return m_worker; }
			virtual void set_arguments() = 0; // Override so m_arguments can be set inside run automatically

		protected:
			void construct_execvp_arguments();
			void clear_execvp_arguments() noexcept;
			char*const* get_execvp_arguments();

			std::optional<pid_t> m_worker;
			std::filesystem::path m_program;
			std::list<std::string> m_arguments;
			std::vector<char*> m_arguments_for_execvp;
	};
}
