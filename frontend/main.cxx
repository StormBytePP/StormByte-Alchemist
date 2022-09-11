#include "application.hxx"

int main(int argc, char **argv) {
	return StormByte::VideoConvert::Application::get_instance().run(argc, argv);
}
