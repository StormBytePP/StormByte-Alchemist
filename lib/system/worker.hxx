#pragma once

#include "visibility.h"

#include <memory>

namespace Alchemist::System {
	class Executable;
	class DLL_PUBLIC Worker {
		public:
			Worker(std::unique_ptr<Executable>&&);
			Worker(const Worker&)				= delete;
			Worker(Worker&&)					= default;
			Worker& operator=(const Worker&)	= delete;
			Worker& operator=(Worker&&)			= default;
			~Worker()							= default;

		private:
			std::unique_ptr<Executable> m_executable;
	};
}