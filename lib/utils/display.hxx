#pragma once

#include <string>
#include <list>

namespace StormByte::VideoConvert::Utils {
	class Display {
		public:
			static std::string list_to_string(const std::list<std::string>& list_of_strings, const std::string& pre = "[ ", const std::string& separator = ",", const std::string& post = " ]");
			static std::string list_to_string(const std::list<int>& list_of_ints, const std::string& pre = "[ ", const std::string& separator = ",", const std::string& post = " ]");
	};
}
