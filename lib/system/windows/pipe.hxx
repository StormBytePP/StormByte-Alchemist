#pragma once

#include "visibility.h"

#include <optional>
#include <string>
#include <windows.h>

namespace Alchemist::System::Windows {
	class DLL_PUBLIC Pipe {
		public:
			Pipe();
			Pipe(const Pipe&)				= delete;
			Pipe(Pipe&&)					= default;
			Pipe& operator=(const Pipe&)	= delete;
			Pipe& operator=(Pipe&&)			= default;
			~Pipe();

			void bind_read(int);
			void bind_read(Pipe&);
			void bind_write(int);
			void bind_write(Pipe&);
			void close_read();
			void close_write();
			int poll(int) const;
			bool has_read_event(unsigned short) const;
			bool has_write_event(unsigned short) const;


			Pipe& operator<<(const std::string&);
			std::optional<std::string>& operator>>(std::optional<std::string>&) const;

		private:
			void write(const std::string&);
			std::optional<std::string> read() const;
			void bind(int&, int);
			void close(HANDLE&);
			void init();

			HANDLE m_fd[2];
			static SECURITY_ATTRIBUTES m_sAttr;
			static constexpr unsigned int MAX_BYTES = 500 * 1024; // 500KB
	};
}