#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist {
	class DLL_PUBLIC Info {
		public:
			static const std::string							Name;
			static const std::string							Author;
			static const std::string							Version;
			static const std::string							URI;
	};
}