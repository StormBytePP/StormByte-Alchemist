#include <media/info.hxx>
#include <media/encoder.hxx>

#include <iostream>

int main() {
	std::cout << "Available codecs: " << std::endl;
	for (auto item: Alchemist::Media::Info::Codec::All) {
		std::cout << item.short_name << ": " << item.long_name << std::endl;
	}
	std::cout << "Selecting Fraunhoffer encoding: ";
	try {
		auto enc = Alchemist::Media::Encoder::Instance(Alchemist::Media::Encoder::AAC_FRAUNHOFFER);
		std::cout << "id is " << enc->get_encoder_type();
	}
	catch(const std::runtime_error& err) {
		std::cout << "(" << err.what() << ")";
	}
	std::cout << std::endl;
	return 0;
}