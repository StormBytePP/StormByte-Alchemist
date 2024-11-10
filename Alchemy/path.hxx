#pragma once

#include <Alchemy/visibility.h>

#include <filesystem>

namespace Alchemy {
	struct ALCHEMY_PUBLIC Path {
		public:
			static const std::filesystem::path Home();
			static const std::filesystem::path Conf();
			static const std::filesystem::path Expand(const std::string&);
			#ifdef WINDOWS
			static const std::filesystem::path Expand(const std::wstring&);
			#endif

		private:
			static const std::string			ExpandEnvironmentVariable(const std::string&);
			#ifdef WINDOWS
			static const std::string			ExpandEnvironmentVariable(const std::wstring&);
			static std::string					UTF8Encode(const std::wstring&);
			static std::wstring					UTF8Decode(const std::string&);
			#endif
	};
}