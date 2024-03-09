#pragma once

#include "visibility.h"

#include <iostream>
#include <optional>
#include <string>
#include <unistd.h>

namespace Alchemist {
	class DLL_PUBLIC Executable {
		public:
			Executable(const std::string&, const std::string&);
			Executable(std::string&&, std::string&&);
			Executable(const Executable&)				= delete;
			Executable(Executable&&)					= default;
			Executable& operator=(const Executable&)	= delete;
			Executable& operator=(Executable&&)			= default;
			~Executable()								= default;

			void run();
			int wait();

			struct _EoF {};
			static constexpr _EoF EoF = {};

			Executable& operator>>(Executable&);
			friend Executable& DLL_PUBLIC operator>>(const std::string&, Executable&);
			friend Executable& DLL_PUBLIC operator>>(const _EoF&, Executable&);
			friend std::ostream& DLL_PUBLIC operator<<(std::ostream&, const Executable&);
			friend std::string& DLL_PUBLIC operator<<(std::string&, const Executable&);
			Executable& operator<<(const std::string&);
			Executable& operator<<(const _EoF&);

			

		private:
			void write(const std::string&);
			std::string read() const;
			void eof();
			void close(int&);

			std::string m_program, m_arguments;
			std::optional<pid_t> m_pid;
			int m_handle[2];
			std::optional<Executable*> m_redirected;
			static constexpr int BUFFER_SIZE = 1;
			bool m_is_eof;
	};
}