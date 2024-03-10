#pragma once

#include "visibility.h"

#include <optional>
#include <stddef.h>
#include <string>

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
			void bind_write(int);
			void close_read();
			void close_write();


			Pipe& operator<<(const std::string&);
			Pipe& operator<<(Pipe&);
			std::optional<std::string>& operator>>(std::optional<std::string>&) const;
			Pipe& operator>>(Pipe&) const;

		private:
			void write(const std::string&);
			std::optional<std::string> read() const;
			void bind(int&, int);
			void close(int&);

			int m_fd[2];
			static constexpr ssize_t MAX_BYTES = 1024 * 1024; // 1MB
	};
}