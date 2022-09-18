#include "base.hxx"

using namespace StormByte::VideoConvert;

Task::Config::CLI::Base::Base(std::shared_ptr<Configuration> config, const unsigned short& req_mask):Task::Config::Base(config, req_mask) {}

Task::Config::CLI::Base::Base(int argc, char* argv[]):Task::Config::Base(Types::config_t()), m_argc(argc), m_argv(argv) {}

Task::Config::CLI::Base::~Base() {}
