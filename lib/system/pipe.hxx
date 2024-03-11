#pragma once

#include "visibility.h"

#include <optional>
#include <stddef.h>
#include <string>
#include <sys/poll.h>

namespace Alchemist::System {
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


			Pipe& operator<<(const std::string&);
			Pipe& operator<<(Pipe&);
			std::optional<std::string>& operator>>(std::optional<std::string>&) const;

		private:
			void write(const std::string&);
			std::optional<std::string> read() const;
			void bind(int&, int);
			void close(int&);
			void init();

			int m_fd[2];
			mutable pollfd m_fd_data[2];
			static constexpr ssize_t MAX_BYTES = 1024 * 1024; // 1MB
	};
}