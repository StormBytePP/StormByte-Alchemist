#include "executable.hxx"

#include <stdexcept>
#include <sys/wait.h>

Alchemist::Executable::Executable(const std::string& prog, const std::string& args):m_program(prog), m_arguments(args) {
	pipe(m_handle);
}

Alchemist::Executable::Executable(std::string&& prog, std::string&& args):m_program(std::move(prog)), m_arguments(std::move(args)) {
	pipe(m_handle);
}

Alchemist::Executable& Alchemist::Executable::operator>>(Executable& exe) {
	return exe;
}

Alchemist::Executable& Alchemist::operator>>(const std::string& str, Alchemist::Executable& exe) {
	exe.write(str);
	return exe;
}

std::ostream& Alchemist::operator<<(std::ostream& o, const Alchemist::Executable& exe) {
	return o << exe.read();
}

Alchemist::Executable& Alchemist::Executable::operator<<(const std::string& str) {
	write(str);
	return *this;
}

Alchemist::Executable& Alchemist::Executable::operator<<(const Alchemist::Executable::_EoF&) {
	close(m_handle[1]);
	return *this;
}

void Alchemist::Executable::run() {
	m_pid = fork();

	if (m_pid == -1) throw std::runtime_error("Can not execute " + m_program);
	else if (m_pid == 0) {
		dup2(m_handle[0], STDIN_FILENO);
		dup2(m_handle[1], STDOUT_FILENO);
		close(m_handle[0]);
		close(m_handle[1]);

		char *argv[] = {m_program.data(), NULL};
		if (execvp(argv[0], argv) < 0) exit(0);
	}
}

int Alchemist::Executable::wait() {
	int status = -1;
	if (m_pid) {
		waitpid(*m_pid, &status, 0);
		m_pid.reset();
	}
	return status;
}

std::string Alchemist::Executable::read() const {
	std::string result = "";
	if (m_pid && m_handle[0] > 0) {
		char buffer[BUFFER_SIZE];
		ssize_t bytes = 0;
		do {
			bytes = ::read(m_handle[0], buffer, BUFFER_SIZE);
			if (bytes > 0) {
				result += std::string(buffer, bytes);
			}
		} while (bytes == BUFFER_SIZE);
	}
	return result;
}

void Alchemist::Executable::write(const std::string& str) {
	if (m_pid && m_handle[1] > 0) {
		::write(m_handle[1], str.c_str(), sizeof(str.get_allocator()) * str.length());
	}
}
