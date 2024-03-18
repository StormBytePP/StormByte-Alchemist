#include <info.hxx>
#include <media/file.hxx>

#include <iostream>

int main() {
	std::cout << "Path to programs (prefix " << Alchemist::Info::prefix() << ")" << std::endl;
	std::cout << "* ffmpeg: " << Alchemist::Info::ffmpeg_path() << std::endl;;
	std::cout << "* ffprobe: " << Alchemist::Info::ffprobe_path() << std::endl;;
	std::cout << "* hdr10plus_tool: " << Alchemist::Info::hdr10plus_tool_path() << std::endl;;

	/*
	std::unique_ptr<Alchemist::Media::File> f;

	f = std::make_unique<Alchemist::Media::File>("/StormWarehouse/PRUEBAPELI/prueba_con.mkv");
	std::cout << "File 1" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR))
		std::cout << "* Has HDR" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR_PLUS))
		std::cout << "* Has HDR+" << std::endl;

	f = std::make_unique<Alchemist::Media::File>("/StormWarehouse/PRUEBAPELI/prueba_sin.mkv");
	std::cout << "File 2" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR))
		std::cout << "* Has HDR" << std::endl;
	if (f->has_feature(Alchemist::Media::Feature::HDR_PLUS))
		std::cout << "* Has HDR+" << std::endl;
	*/

	return 0;
}

