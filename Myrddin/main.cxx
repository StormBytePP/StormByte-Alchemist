#include <iostream>

#include <system/config.hxx>

using namespace Alchemist::System;

int main() {
	std::cout << "Before: " << Config::Instance.GetDatabaseFile() << std::endl;
	Config::Instance.SetDatabaseFile("/tmp/my_database.sqlite3");
	std::cout << "After: " << Config::Instance.GetDatabaseFile() << std::endl;
	Config::Instance.Save();
	return 0;
}

/* Testing main 1
int main() {
	std::unique_ptr<Alchemist::Media::File::InFile> f;

	std::cout << "File 1:" << std::endl;
	#ifdef LINUX
	f = std::make_unique<Alchemist::Media::File::InFile>("/StormWarehouse/PRUEBAPELI/prueba_con.mkv");
	#else
	f = std::make_unique<Alchemist::Media::File::InFile>("D:\\PRUEBAPELI\\prueba_con.mkv");
	#endif
	if (f->has_feature(Alchemist::Media::Feature::HDR))
		std::cout << "* Has HDR" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR_PLUS))
		std::cout << "* Has HDR+" << std::endl;

	std::cout << "File 2:" << std::endl;
	#ifdef LINUX
	f = std::make_unique<Alchemist::Media::File::InFile>("/StormWarehouse/PRUEBAPELI/prueba_sin.mkv");
	#else
	f = std::make_unique<Alchemist::Media::File::InFile>("D:\\PRUEBAPELI\\prueba_sin.mkv");
	#endif
	if (f->has_feature(Alchemist::Media::Feature::HDR))
		std::cout << "* Has HDR" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR_PLUS))
		std::cout << "* Has HDR+" << std::endl;

	return 0;
}
*/
