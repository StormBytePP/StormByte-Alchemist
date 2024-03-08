#include <info.hxx>

#include <iostream>

int main() {
	std::cout << "FFmpeg path is: " << Alchemist::Info::ffmpeg_path() << std::endl;
	return 0;
}