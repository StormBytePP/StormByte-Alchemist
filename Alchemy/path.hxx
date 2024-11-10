#pragma once

#include <Alchemy/visibility.h>

#include <filesystem>

namespace Alchemy {
	struct ALCHEMY_PUBLIC Path {
		public:
			static const std::filesystem::path Home();
			static const std::filesystem::path Conf();
	};
}