#pragma once

#include "types.hxx"

namespace StormByte::VideoConvert::Utils {
	class Filesystem {
		public:
			static bool is_folder_writable(const Types::path_t& fullpath, const bool& use_cerr = false);
			static bool is_folder_readable(const Types::path_t& fullpath, const bool& use_cerr = false);
			static bool is_folder_readable_and_writable(const Types::path_t& fullpath, const bool& use_cerr = false);
			static bool exists_file(const Types::path_t& fullpath, const bool& use_cerr = false);
	};
}
