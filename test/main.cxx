#include <media/media.hxx>
#include <iostream>

int main() {
	std::cout << "Available codecs: " << std::endl;
	for (auto codec : StormByte::VideoConvert::Media::Encoders::Available) {
		auto entry = StormByte::VideoConvert::Media::Encoders::Names.at(codec);
		std::cout << "   * " << entry.first << ": " << entry.second << std::endl; 
	}
	return 0;
}