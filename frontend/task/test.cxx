#include "test.hxx"

using namespace StormByte::VideoConvert;

Frontend::Task::Test::Test(Types::config_t config):VideoConvert::Task::Config::CLI::Base(config, VideoConvert::Task::Config::REQUIRE_DATABASE | VideoConvert::Task::Config::REQUIRE_LOGGER) {}

StormByte::VideoConvert::Task::STATUS Frontend::Task::Test::do_work(std::optional<pid_t>&) noexcept {
	return VideoConvert::Task::HALT_OK;
}
