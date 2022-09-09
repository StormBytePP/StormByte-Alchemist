#pragma once

#include <filesystem>

namespace StormByte::VideoConvert::Utils {
	class Filesystem {
		public:
			static bool is_folder_writable(const std::filesystem::path& fullpath, bool use_cerr = false);
			static bool is_folder_readable(const std::filesystem::path& fullpath, bool use_cerr = false);
			static bool is_folder_readable_and_writable(const std::filesystem::path& fullpath, bool use_cerr = false);
			static bool exists_file(const std::filesystem::path& fullpath, bool use_cerr = false);
	};
}
