#include <media/codec.hxx>
#include <media/decoder.hxx>
#include <media/encoder.hxx>

#include <iostream>

int main() {
	std::cout << "Available codecs: " << std::endl;
	for (auto codec : StormByte::Alchemist::Media::Codec::Available()) {
		auto info = StormByte::Alchemist::Media::Codec::Metadata().at(codec);
		std::cout << "   * " << info.first << ": " << info.second << std::endl; 
	}
	std::cout << "Available decoders: " << std::endl;
	for (auto codec : StormByte::Alchemist::Media::Decoder::Available()) {
		auto info = StormByte::Alchemist::Media::Decoder::Metadata().at(codec);
		std::cout << "   * " << info.first << ": " << info.second << std::endl; 
	}
	std::cout << "Available encoders: " << std::endl;
	for (auto codec : StormByte::Alchemist::Media::Encoder::Available()) {
		auto info = StormByte::Alchemist::Media::Encoder::Metadata().at(codec);
		std::cout << "   * " << info.first << ": " << info.second << std::endl; 
	}

	return 0;
}