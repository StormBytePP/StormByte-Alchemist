#include <iostream>

#include <media/file.hxx>

using namespace Alchemist::Media;

int main() {
	File file("/StormWarehouse/MakeMKV/Final/El Señor de los Anillos - 1 - La Comunidad del Anillo - Extendida.mkv");
	//File file("/tmp/Regreso al Futuro - 1 - m4K HDR+.mkv");
	//File file("/tmp/Tokyo Gore Police (V.O.Sub.Español) 2008 DVDRIP Xvid-Mp3 (Estrenos-Sub.com) by CratosXP.avi");
	std::cout << "File size is " << file.GetSize() << " bytes (" << file.GetSize() / 1073741824.0 << "GB)" << std::endl;
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
