#include <iostream>

#include <system/config.hxx>

using namespace Alchemist::System;

#include <iostream>

int main() {
	Config& cfg = Config::Instance();

	std::cout << "libx265 options: ";
	Config::Codec codec = cfg.GetCodec("libx265");
	if (codec.options)
		std::cout << "\"" << *codec.options << "\"" <<  std::endl;
	else
		std::cout << "(not available)" << std::endl;

	return 0;
}

