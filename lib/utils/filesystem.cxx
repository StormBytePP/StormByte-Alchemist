#include "filesystem.hxx"

#include <iostream>
#include <unistd.h>

bool StormByte::VideoConvert::Utils::Filesystem::is_folder_writable(const std::filesystem::path& fullpath, bool use_cerr) {
	if (access(fullpath.c_str(), W_OK) == 0)
		return true;
	else {
		if (use_cerr) std::cerr << "Folder " << fullpath << " is not writable!" << std::endl;
		return false;
	}
}

bool StormByte::VideoConvert::Utils::Filesystem::exists_file(const std::filesystem::path& fullpath, bool use_cerr) {
	if (std::filesystem::exists(fullpath))
		return true;
	else {
		if (use_cerr) std::cerr << "File " << fullpath << " does not exist" << std::endl;
		return false;
	}
}
