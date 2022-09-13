#include "application.hxx"
#include "ffmpeg/ffmpeg.hxx"

using namespace StormByte::VideoConvert;

int main(int argc, char **argv) {
	return Application::get_instance().run(argc, argv);

	//FFmpeg f1(1, "/tmp/u.mkv"), f2 = f1;

	//return 0;
}
