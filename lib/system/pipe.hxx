#pragma once

#include "visibility.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

#ifdef WINDOWS
#include <windows.h>
#else
#include <sys/poll.h>
#endif

namespace Alchemist::System {
	class DLL_PUBLIC Pipe {
		public:
			static constexpr size_t MAX_READ_BYTES		= 4 * 1024 * 1024; // 4MiB

			Pipe();
			Pipe(const Pipe&)				= delete;
			Pipe(Pipe&&)					= default;
			Pipe& operator=(const Pipe&)	= delete;
			Pipe& operator=(Pipe&&)			= default;
			~Pipe();

			#ifdef LINUX
			void bind_read(int);
			void bind_read(Pipe&);
			void bind_write(int);
			void bind_write(Pipe&);
			ssize_t write(const std::string&);
			bool write_eof() const;
			ssize_t read(std::vector<char>&, ssize_t) const;
			bool read_eof() const;
			#else
			void set_read_handle_information(DWORD, DWORD);
			void set_write_handle_information(DWORD, DWORD);
			HANDLE get_read_handle() const;
			HANDLE get_write_handle() const;
			DWORD write(const std::string&);
			DWORD read(std::vector<CHAR>&, DWORD) const;
			bool write_atomic(std::string&&);
			#endif
			void close_read();
			void close_write();

			Pipe& operator<<(const std::string&);
			std::optional<std::string>& operator>>(std::optional<std::string>&) const;

		private:
			#ifdef LINUX
			void bind(int&, int);
			void close(int&);
			#else
			void close(HANDLE&);
			void set_handle_information(HANDLE, DWORD, DWORD);
			#endif

			#ifdef WINDOWS
			HANDLE m_fd[2];
			static SECURITY_ATTRIBUTES m_sAttr;
			#else
			int m_fd[2];
			#endif
			
	};
}