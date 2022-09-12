#include "filesystem.hxx"

#include <iostream>
#include <unistd.h>

using namespace StormByte::VideoConvert;

bool Utils::Filesystem::is_folder_writable(const std::filesystem::path& fullpath, const bool& use_cerr) {
	if (access(fullpath.c_str(), W_OK) == 0)
		return true;
	else {
		if (use_cerr) std::cerr << "Folder " << fullpath << " is not writable!" << std::endl;
		return false;
	}
}

bool Utils::Filesystem::is_folder_readable(const std::filesystem::path& fullpath, const bool& use_cerr) {
	if (access(fullpath.c_str(), R_OK) == 0)
		return true;
	else {
		if (use_cerr) std::cerr << "Folder " << fullpath << " is not readable!" << std::endl;
		return false;
	}
}

bool Utils::Filesystem::is_folder_readable_and_writable(const std::filesystem::path& fullpath, const bool& use_cerr) {
	if (!is_folder_readable(fullpath) || !is_folder_writable(fullpath)) {
		if (use_cerr) std::cerr << "Folder " << fullpath << " is not readable and writable!" << std::endl;
		return false;
	}
	else
		return true;
}

bool Utils::Filesystem::exists_file(const std::filesystem::path& fullpath, const bool& use_cerr) {
	if (std::filesystem::exists(fullpath))
		return true;
	else {
		if (use_cerr) std::cerr << "File " << fullpath << " does not exist" << std::endl;
		return false;
	}
}
