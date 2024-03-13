#pragma once

#include "visibility.h"

#include <memory>
#include <optional>
#include <string>

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

			#ifdef LINUX
			void bind_read(int);
			void bind_read(Pipe&);
			void bind_write(int);
			void bind_write(Pipe&);
			#endif
			void close_read();
			void close_write();
			#ifdef LINUX
			int poll(int) const;
			bool has_read_event(unsigned short) const;
			bool has_write_event(unsigned short) const;
			#endif

			Pipe& operator<<(const std::string&);
			std::optional<std::string>& operator>>(std::optional<std::string>&) const;

		private:
			void write(const std::string&);
			std::optional<std::string> read() const;
			#ifdef LINUX
			void bind(int&, int);
			#endif
			void close(int&);
			void init();

			#ifdef WINDOWS
			HANDLE m_fd[2];
			static SECURITY_ATTRIBUTES m_sAttr;
			#else
			int m_fd[2];
			mutable pollfd m_fd_data[2];
			#endif
			static constexpr size_t MAX_BYTES = 500 * 1024; // 500KB
	};
}