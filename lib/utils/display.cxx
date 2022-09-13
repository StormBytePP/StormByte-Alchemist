#include "display.hxx"

using namespace StormByte::VideoConvert;

std::string Utils::Display::list_to_string(const std::list<std::string>& list_of_strings, const std::string& pre, const std::string& separator, const std::string& post) {
	std::string result = pre;
	unsigned int counter = 1;
	
	for (auto it = list_of_strings.begin(); it != list_of_strings.end(); it++, counter++) {
		result += *it;
		if (counter < list_of_strings.size()) result += separator;
	}
	result += post;

	return result;
}
