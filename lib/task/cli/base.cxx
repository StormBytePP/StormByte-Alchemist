#include "base.hxx"

using namespace StormByte::VideoConvert;

Task::CLI::Base::Base(int argc, char** argv):Task::Base(), m_argc(argc), m_argv(argv) {}

Task::CLI::Base::~Base() {}
