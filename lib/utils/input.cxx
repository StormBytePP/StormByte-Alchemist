#include "input.hxx"

#include <cstdlib>
#include <iostream>
#include <algorithm>

bool StormByte::VideoConvert::Utils::Input::to_int(const std::string& possible_number, int& store, bool use_cerr) {
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

bool StormByte::VideoConvert::Utils::Input::to_int_positive(const std::string& possible_number, int& store, bool use_cerr) {
	if (to_int(possible_number, store, use_cerr)) {
		if (store < 0) {
			if (use_cerr) std::cerr << "Introduced number is not a positive integer" << std::endl;
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

bool StormByte::VideoConvert::Utils::Input::to_int_in_range(const std::string& possible_number, int& store, int min, int max, bool use_cerr) {
	return to_int(possible_number, store, use_cerr) && in_range(store, min, max, use_cerr);
}

bool StormByte::VideoConvert::Utils::Input::in_range(int number, int min, int max, bool use_cerr) {
	if (number>=min && number<=max)
		return true;
	else {
		if (use_cerr) std::cerr << "Number " << number << " is not in range between " << min << " and " << max << std::endl;
		return false;
	}
}

bool StormByte::VideoConvert::Utils::Input::in_options(const std::string& input, const std::list<std::string>& options, bool use_cerr) {
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

std::string StormByte::VideoConvert::Utils::Input::list_to_string(const std::list<std::string>& list_of_strings) {
	std::string result ="[ ";
	
	for (std::string i: list_of_strings)
		result += i + " ";
	result += "]";

	return result;
}

