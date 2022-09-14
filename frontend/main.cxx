#include "application.hxx"

using namespace StormByte::VideoConvert;

int main(int argc, char **argv) {
	return Application::get_instance().run(argc, argv);
}
