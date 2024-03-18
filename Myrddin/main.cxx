#include <info.hxx>
#include <media/file.hxx>

#include <iostream>

int main() {
	std::unique_ptr<Alchemist::Media::File> f;

	std::cout << "File 1:" << std::endl;
	try {
		#ifdef LINUX
		f = std::make_unique<Alchemist::Media::File>("/StormWarehouse/PRUEBAPELI/prueba_con.mkv");
		#else
		f = std::make_unique<Alchemist::Media::File>("D:\\PRUEBAPELI\\prueba_con.mkv");
		#endif
		if (f->has_feature(Alchemist::Media::Feature::HDR))
			std::cout << "* Has HDR" << std::endl;
		if (f->has_feature(Alchemist::Media::Feature::HDR_PLUS))
			std::cout << "* Has HDR+" << std::endl;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}

	std::cout << "File 2" << std::endl;
	try {
		#ifdef LINUX
		f = std::make_unique<Alchemist::Media::File>("/StormWarehouse/PRUEBAPELI/prueba_sin.mkv");
		#else
		f = std::make_unique<Alchemist::Media::File>("D:\\PRUEBAPELI\\prueba_sin.mkv");
		#endif
		if (f->has_feature(Alchemist::Media::Feature::HDR))
			std::cout << "* Has HDR" << std::endl;
		if (f->has_feature(Alchemist::Media::Feature::HDR_PLUS))
			std::cout << "* Has HDR+" << std::endl;
	}
	catch (const std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}

	return 0;
}

