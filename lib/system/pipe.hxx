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
			Pipe();
			Pipe(const Pipe&)				= delete;
			Pipe(Pipe&&)					= default;
			Pipe& operator=(const Pipe&)	= delete;
			Pipe& operator=(Pipe&&)			= default;
			~Pipe();

			static constexpr size_t MAX_READ_BYTES = 4 * 1024 * 1024; // 4MiB

			#ifdef LINUX
			void bind_read(int);
			void bind_read(Pipe&);
			void bind_write(int);
			void bind_write(Pipe&);
			int poll(int) const;
			bool has_read_event(unsigned short) const;
			bool has_write_event(unsigned short) const;
			ssize_t write(const std::string&);
			ssize_t read(std::vector<char>&, ssize_t) const;
			#else
			void set_read_handle_information(DWORD, DWORD);
			void set_write_handle_information(DWORD, DWORD);
			HANDLE get_read_handle() const;
			HANDLE get_write_handle() const;
			DWORD write(const std::string&);
			DWORD read(std::vector<CHAR>&, DWORD) const;
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
			mutable std::vector<CHAR> m_buffer;
			#else
			int m_fd[2];
			mutable pollfd m_fd_data[2];
			#endif
			
	};
}