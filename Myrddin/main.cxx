#include <iostream>

#include <system/config.hxx>

using namespace Alchemist::System;

#include <iostream>

int main() {
	Config& cfg = Config::Instance;

	std::cout << "Temp directory is: " << cfg.GetTmpDirectory() << std::endl;

	cfg.Write();
	return 0;
}

