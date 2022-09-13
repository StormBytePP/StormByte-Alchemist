#include "test.hxx"

using namespace StormByte::VideoConvert;

Task::Test& Task::Test::get_instance() {
	static Test instance;
	return instance;
}

Task::STATUS Task::Test::run(std::shared_ptr<Configuration> config) noexcept {
	if (Base::run(config) == RUNNING) {
		// Currently there are no aditional actions but they are possible here
		m_status = HALT_OK;
	}

	return m_status;
}
