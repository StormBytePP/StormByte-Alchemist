#pragma once

#include "system/pipe.hxx"

#include <iostream>
#include <optional>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

namespace Alchemist {
	class DLL_PUBLIC Executable {
		public:
			Executable(const std::string& prog, const std::vector<std::string>& args = std::vector<std::string>());
			Executable(std::string&&, std::vector<std::string>&&);
			Executable(const Executable&)				= delete;
			Executable(Executable&&)					= default;
			Executable& operator=(const Executable&)	= delete;
			Executable& operator=(Executable&&)			= default;
			~Executable()								= default;

			int wait();

			struct _EoF {};
			static constexpr _EoF EoF = {};

			Executable& operator>>(Executable&);
			std::optional<std::string>& operator>>(std::optional<std::string>&);
			friend std::ostream& DLL_PUBLIC operator<<(std::ostream&, const Executable&);
			Executable& operator<<(const std::string&);
			void operator<<(const _EoF&);

		public:
			void write(const std::string&);
			void run();
			void consume_and_redirect(Executable*);

			std::string m_program;
			std::vector<std::string> m_arguments;
			pid_t m_pid;
			System::Pipe m_pstdout, m_pstdin, m_pstderr;
			std::optional<Executable*> m_redirected;
			static constexpr ssize_t BUFFER_SIZE = 1024 * 1024; // 1MiB
			std::optional<std::thread> m_syncer;
	};
}