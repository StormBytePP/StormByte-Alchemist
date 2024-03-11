#pragma once

#include "../executable.hxx"
#include "../pipe.hxx"

#include <iostream>
#include <optional>
#include <string>
#include <thread>
#include <vector>

namespace Alchemist::System::Windows {
	class DLL_LOCAL Executable {
		public:
			Executable(const std::string& prog, const std::vector<std::string>& args = std::vector<std::string>());
			Executable(std::string&&, std::vector<std::string>&&);
			Executable(const Executable&)				= delete;
			Executable(Executable&&)					= default;
			Executable& operator=(const Executable&)	= delete;
			Executable& operator=(Executable&&)			= default;
			~Executable()								= default;

			int wait();

			Executable& operator>>(Executable&);
			std::optional<std::string>& operator>>(std::optional<std::string>&);
			friend std::ostream& DLL_LOCAL operator<<(std::ostream&, const Executable&);
			Executable& operator<<(const std::string&);
			void operator<<(const System::Executable::_EoF&);

		public:
			void write(const std::string&);
			void run();
			void consume_and_forward(Executable&);

			std::string m_program;
			std::vector<std::string> m_arguments;
			System::Pipe m_pstdout, m_pstdin, m_pstderr;
			std::unique_ptr<std::thread> m_forwarder;
	};
}