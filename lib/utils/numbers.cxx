#include "numbers.hxx"

#include <cstdlib>

bool StormByte::VideoConvert::Utils::Numbers::to_int(const char* possible_number, int& store) {
	char *endptr;
	store = strtol(possible_number, &endptr, 10);

	return *endptr == '\0';
}
