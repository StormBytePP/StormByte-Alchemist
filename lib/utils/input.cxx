#include "input.hxx"

#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace StormByte::VideoConvert;

bool Utils::Input::to_int(const std::string& possible_number, int& store, const bool& use_cerr) {
	char *endptr;
	store = strtol(possible_number.c_str(), &endptr, 10);

	if (*endptr == '\0' && !possible_number.empty()) {
		return true;
	}
	else {
		if (use_cerr) std::cerr << "Input \"" << possible_number << "\" is not fully a recognized number" << std::endl;
		return false;
	}
}

bool Utils::Input::to_int_positive(const std::string& possible_number, int& store, const bool& use_cerr) {
	return to_int_minimum(possible_number, store, 0, use_cerr);
}

bool Utils::Input::to_int_minimum(const std::string& possible_number, int& store, const int& minimum, const bool& use_cerr) {
	if (to_int(possible_number, store, use_cerr)) {
		if (store < minimum) {
			if (use_cerr) std::cerr << "Introduced number is lesser than minimum value " << minimum << " required" << std::endl;
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

bool Utils::Input::to_int_in_range(const std::string& possible_number, int& store, const int& min, const int& max, const bool& use_cerr) {
	return to_int(possible_number, store, use_cerr) && in_range(store, min, max, use_cerr);
}

bool Utils::Input::in_range(const int& number, const int& min, const int& max, const bool& use_cerr) {
	if (number>=min && number<=max)
		return true;
	else {
		if (use_cerr) std::cerr << "Number " << number << " is not in range between " << min << " and " << max << std::endl;
		return false;
	}
}

bool Utils::Input::in_options(const std::string& input, const std::list<std::string>& options, const bool& use_cerr) {
	if (std::find(options.begin(), options.end(), input) == options.end()) {
		if (use_cerr) {
			std::cerr << "Selected option " << input << " not found in " << list_to_string(options) << std::endl;
		}
		return false;
	}
	else {
		return true;
	}
}

std::string Utils::Input::list_to_string(const std::list<std::string>& list_of_strings) {
	std::string result ="[ ";
	
	for (std::string i: list_of_strings)
		result += i + " ";
	result += "]";

	return result;
}

