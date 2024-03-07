#include <media/info.hxx>

#include <iostream>

int main() {
	std::cout << "Available codecs: " << std::endl;
	for (auto item: Alchemist::Media::Info::Codec::All) {
		std::cout << item.short_name << ": " << item.long_name << std::endl;
	}
	return 0;
}