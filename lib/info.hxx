#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist {
	class DLL_PUBLIC Info {
		public:
			static const std::string DLL_PUBLIC Name;
			static const std::string DLL_PUBLIC Author;
			static const std::string DLL_PUBLIC Version;
			static const std::string DLL_PUBLIC URI;
	};
}