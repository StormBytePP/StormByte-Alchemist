#include "input.hxx"
#include "display.hxx"

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace StormByte::VideoConvert;

bool Utils::Input::is_int(const std::string& possible_int, const bool& use_cerr) {
	std::string new_str = possible_int[0] == '-' ? possible_int.substr(1) : possible_int;
	bool result = !possible_int.empty() && std::find_if(new_str.begin(), new_str.end(),
		[](unsigned char c) { return !std::isdigit(c); }) == new_str.end();
	if (!result && use_cerr) {
		std::cerr << possible_int << " is not a number" << std::endl;
	}
	return result;
}

bool Utils::Input::to_int(const std::string& possible_number, int& store, const bool& use_cerr) {
	bool isnumber = is_int(possible_number, use_cerr);

	if (isnumber) {
		char *endptr;
		store = strtol(possible_number.c_str(), &endptr, 10);
		return true;
	}
	else
		return false;
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
			std::cerr << "Selected option " << input << " not found in " << Display::list_to_string(options, "[", " ", "]") << std::endl;
		}
		return false;
	}
	else {
		return true;
	}
}

bool Utils::Input::in_options(const int& input, const std::list<int>& options, const bool& use_cerr) {
	if (std::find(options.begin(), options.end(), input) == options.end()) {
		if (use_cerr) {
			std::cerr << "Selected option " << input << " not found in " << Display::list_to_string(options, "[", " ", "]") << std::endl;
		}
		return false;
	}
	else {
		return true;
	}
}

bool Utils::Input::in_yes_no(const std::string input, bool& store, const bool& use_cerr) {
	bool result = in_options(input, { "y", "Y", "n", "N", "yes", "YES", "no", "NO"}, use_cerr);
	if (result) {
		store = input == "y" || input == "Y" || input == "yes" || input == "YES";
	}
	return result;
}
