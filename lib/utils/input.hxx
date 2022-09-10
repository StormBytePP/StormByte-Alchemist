#pragma once

#include <string>
#include <list>

namespace StormByte::VideoConvert::Utils {
	class Input {
		public:
			static bool to_int(const std::string& possible_number, int& store, bool use_cerr = false);
			static bool to_int_positive(const std::string& possible_number, int& store, bool use_cerr = false);
			static bool to_int_minimum(const std::string& possible_number, int& store, int minimum, bool use_cerr = false);
			static bool to_int_in_range(const std::string& possible_number, int& store, int min, int max, bool use_cerr = false);
			static bool in_range(int number, int min, int max, bool use_cerr = false);
			static bool in_options(const std::string& input, const std::list<std::string>& options, bool use_cerr = false);
			static bool in_options(const std::string& input, const std::list<int>& options, bool use_cerr = false);

		private:	
			static std::string list_to_string(const std::list<std::string>& list_of_strings);
	};
}
