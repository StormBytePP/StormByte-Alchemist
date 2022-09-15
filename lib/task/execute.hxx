#pragma once

#include "base.hxx"

#include <filesystem>

namespace StormByte::VideoConvert::Task {
	class Execute: public Base {
		public:
			Execute(const Types::path_t& program);
			Execute(const Execute& execute);
			Execute(Execute&& execute) noexcept = default;
			Execute& operator=(const Execute& execute);
			Execute& operator=(Execute&& execute) noexcept = default;
			~Execute() noexcept;

			virtual STATUS run(Types::config_t config) noexcept override;

			inline std::optional<pid_t> get_worker() const { return m_worker; }
			virtual void set_arguments() = 0; // Override so m_arguments can be set inside run automatically
			inline std::string get_output() const { return m_output; }

		protected:
			void construct_execvp_arguments();
			void clear_execvp_arguments() noexcept;
			char*const* get_execvp_arguments();

			std::optional<pid_t> m_worker;
			Types::path_t m_program;
			std::list<std::string> m_arguments;
			std::vector<char*> m_arguments_for_execvp;
			std::string m_output;
	};
}
