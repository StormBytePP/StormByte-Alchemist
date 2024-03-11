#pragma once

#include "visibility.h"

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#if defined _WIN32 || defined __CYGWIN__
	namespace Alchemist::System::Windows { class Executable; }
	using ExecImpl = Alchemist::System::Windows::Executable;
#else
	namespace Alchemist::System::Linux { class Executable; }
	using ExecImpl = Alchemist::System::Linux::Executable;
#endif

namespace Alchemist::System {
	class DLL_PUBLIC Executable {
		public:
			struct {} typedef _EoF;
			static constexpr _EoF EoF = {};
			
			Executable(const std::string& prog, const std::vector<std::string>& args = std::vector<std::string>());
			Executable(std::string&&, std::vector<std::string>&&);
			Executable(const Executable&)				= delete;
			Executable(Executable&&)					= default;
			Executable& operator=(const Executable&)	= delete;
			Executable& operator=(Executable&&)			= default;
			~Executable();

			int wait();

			Executable& operator>>(Executable&);
			std::optional<std::string>& operator>>(std::optional<std::string>&);
			friend std::ostream& DLL_PUBLIC operator<<(std::ostream&, const Executable&);
			Executable& operator<<(const std::string&);
			void operator<<(const _EoF&);

		private:
			std::unique_ptr<ExecImpl> m_exec_impl;
	};
}