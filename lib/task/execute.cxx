#include "execute.hxx"
#include "utils/display.hxx"

#include <unistd.h>
#include <sys/wait.h>

using namespace StormByte::VideoConvert;

Task::Execute::Execute(const std::filesystem::path& program):Base(), m_program(program) {
	m_require_logger = true;
}

Task::STATUS Task::Execute::run(std::shared_ptr<Configuration> config) noexcept {
	if (Base::run(config) == RUNNING) {
		set_arguments();
		m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Executing " + m_program.string() + " " + Utils::Display::list_to_string(m_arguments, "", " ", ""));
		pid_t worker = fork();

		if (worker < 0)
			m_status = HALT_ERROR;
		else if (worker == 0)
			execvp(m_program.c_str(), arguments().get()); // Here get() is needed as there is no operator* for this case
		else {
			m_worker = worker;
		}
	}

	return m_status;
}

std::unique_ptr<char*[]> Task::Execute::arguments() const {
	std::unique_ptr<char*[]> args(new  char*[1 + m_arguments.size() + 1]);
	unsigned short counter = 0;
	args[counter++] = const_cast<char*>(m_program.filename().c_str());
	for (auto it = m_arguments.begin(); it != m_arguments.end(); it++, counter++)
		args[counter] = const_cast<char*>(it->c_str());

	args[counter] = nullptr;

	return args;
}
