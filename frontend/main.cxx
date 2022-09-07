#include "application.hxx"

int main(int argc, char **argv) {
	return StormByte::VideoConvert::Application::getInstance().run(argc, argv);
}
