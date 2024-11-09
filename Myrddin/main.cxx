#include <iostream>

#include <Alchemy/config/file.hxx>

using namespace Alchemy::Config;

#include <iostream>

int main() {
	File& cfg = File::Instance();

	std::cout << "libx265 options: ";
	std::optional<Codec> codec = cfg.GetCodec("libx265");
	if (codec && codec->c_options)
		std::cout << "\"" << *codec->c_options << "\"" <<  std::endl;
	else
		std::cout << "(not available)" << std::endl;

	return 0;
}

