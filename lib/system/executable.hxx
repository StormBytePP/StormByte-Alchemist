#pragma once

#include "pipe.hxx"

#include <iostream>
#include <optional>
#include <string>
#include <thread>
#ifdef LINUX
#include <unistd.h>
#endif
#include <vector>

namespace Alchemist::System {
	struct {} typedef _EoF;
	static constexpr _EoF EoF = {};
	class DLL_PUBLIC Executable {
		public:
			Executable(const std::string& prog, const std::vector<std::string>& args = std::vector<std::string>());
			Executable(std::string&&, std::vector<std::string>&&);
			Executable(const Executable&)				= delete;
			Executable(Executable&&)					= default;
			Executable& operator=(const Executable&)	= delete;
			Executable& operator=(Executable&&)			= default;
			~Executable()								= default;
			#ifdef LINUX
			int wait();
			#else
			DWORD wait();
			#endif

			Executable& operator>>(Executable&);
			std::optional<std::string>& operator>>(std::optional<std::string>&);
			friend std::ostream& DLL_LOCAL operator<<(std::ostream&, const Executable&);
			Executable& operator<<(const std::string&);
			void operator<<(const System::_EoF&);

		public:
			void send(const std::string&);
			void run();
			void consume_and_forward(Executable&);
			#ifdef WINDOWS
			std::wstring full_command() const;
			#endif

			std::string m_program;
			std::vector<std::string> m_arguments;
			#ifdef LINUX
			pid_t m_pid;
			#else
			STARTUPINFO m_siStartInfo;
			PROCESS_INFORMATION m_piProcInfo;
			#endif
			System::Pipe m_pstdout, m_pstdin, m_pstderr;
			std::unique_ptr<std::thread> m_forwarder;
	};
}