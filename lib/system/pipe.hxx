#pragma once

#include "visibility.h"

#include <memory>
#include <optional>
#include <string>

#if defined _WIN32 || defined __CYGWIN__
	#include "windows/pipe.hxx"
	using PipeImpl = Alchemist::System::Windows::Pipe;
#else
	#include "linux/pipe.hxx"
	using PipeImpl = Alchemist::System::Linux::Pipe;
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
			std::unique_ptr<PipeImpl> m_pipe_impl;
	};
}