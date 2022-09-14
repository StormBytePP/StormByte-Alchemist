#include "execute.hxx"
#include "utils/display.hxx"

#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace StormByte::VideoConvert;

Task::Execute::Execute(const std::filesystem::path& program):Base(), m_program(program) {
	m_require_logger = true;
}

Task::Execute::Execute(const Execute& exec):m_worker(exec.m_worker), m_program(exec.m_program), m_arguments(exec.m_arguments) {
	construct_execvp_arguments();
}

Task::Execute& Task::Execute::operator=(const Execute& exec) {
	if (&exec != this) {
		m_worker	= exec.m_worker;
		m_program	= exec.m_program;
		m_arguments	= exec.m_arguments;
		construct_execvp_arguments();
	}
	return *this;
}

Task::Execute::~Execute() {
	clear_execvp_arguments();
}

Task::STATUS Task::Execute::run(std::shared_ptr<Configuration> config) noexcept {
	if (Base::run(config) == RUNNING) {
		set_arguments();

		// Setup file descriptors for redirecting stdout
		int file_descriptor[2];
		if (pipe(file_descriptor) == -1) {
			m_logger->message_line(Utils::Logger::LEVEL_ERROR, "Can not create pipes for executing the program " + m_program.string());
			return HALT_ERROR;
		}
		m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Executing " + m_program.string() + " " + Utils::Display::list_to_string(m_arguments, "", " ", ""));
		pid_t worker = fork();

		if (worker < 0) { // Fork error
			m_logger->message_line(Utils::Logger::LEVEL_ERROR, "Can not fork process!");
			m_status = HALT_ERROR;
		}
		else if (worker > 0) { // Fork parent
			m_worker = worker;

			// Close the writing part
			close(file_descriptor[1]);

			// Read and store output
			char buffer[4096];
			bool continue_reading = true;
			while (continue_reading) {
				ssize_t count = read(file_descriptor[0], buffer, sizeof(buffer));
				if (count == -1) {
					if (errno == EINTR) {
						continue;
					} 
				} else if (count == 0) {
						continue_reading = false;
				} else {
					m_output += std::string().assign(buffer, count);
				}
			}
			close(file_descriptor[0]);
		}
		else { // Fork child
			while ((dup2(file_descriptor[1], STDOUT_FILENO) == -1) && (errno == EINTR)) {}
			close(file_descriptor[1]);
			close(file_descriptor[0]);
			execvp(m_program.c_str(), get_execvp_arguments()); // Here get() is needed as there is no operator* for this case
		}
	}

	return m_status;
}

char*const* Task::Execute::get_execvp_arguments() {
	if (m_arguments_for_execvp.empty())
		construct_execvp_arguments();

	return m_arguments_for_execvp.data();
}

void Task::Execute::clear_execvp_arguments() noexcept {
	for (size_t i = 0; i < m_arguments_for_execvp.size(); i++)
		free(m_arguments_for_execvp[i]);
	m_arguments_for_execvp.clear();
}

void Task::Execute::construct_execvp_arguments() {
	clear_execvp_arguments();
	m_arguments_for_execvp.reserve(1 + m_arguments.size() + 1);
	m_arguments_for_execvp.push_back(strdup(m_program.string().c_str()));
	for (auto it = m_arguments.begin(); it != m_arguments.end(); it++)
		m_arguments_for_execvp.push_back(strdup(it->c_str()));
	m_arguments_for_execvp.push_back(nullptr);
}
