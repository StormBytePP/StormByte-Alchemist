#include "executable.hxx"

#include <filesystem>
#include <stdexcept>
#include <sys/wait.h>

Alchemist::Executable::Executable(const std::string& prog, const std::vector<std::string>& args):m_program(prog), m_arguments(args), m_is_eof(false) {
	run();
}

Alchemist::Executable::Executable(std::string&& prog, std::vector<std::string>&& args):m_program(std::move(prog)), m_arguments(std::move(args)), m_is_eof(false) {
	run();
}

Alchemist::Executable& Alchemist::Executable::operator>>(Executable& exe) {
	if (m_is_eof) {
		// We are attaching an already EOF'ed item so we have to
		// rewrite the pending data
		const std::string pending = read();
		if (!pending.empty()) {
			exe.write(pending);
		}
		exe.eof();
	}
	else {
		dup2(exe.m_handle[1], m_handle[1]);
		close(exe.m_handle[1]);

		// We write pending data
		write(read());
		close(m_handle[0]);
		m_redirected = &exe;
		if (m_is_eof) exe.eof();
	}
	return exe;
}

Alchemist::Executable& Alchemist::operator>>(const std::string& str, Alchemist::Executable& exe) {
	exe.write(str);
	return exe;
}

Alchemist::Executable& Alchemist::operator>>(const Alchemist::Executable::_EoF& _eof, Executable& exec) {
	exec << _eof;
	return exec;
}

std::ostream& Alchemist::operator<<(std::ostream& o, const Alchemist::Executable& exe) {
	return o << exe.read();
}

std::string& Alchemist::operator<<(std::string& str, const Executable& exe) {
	str = exe.read();
	return str;
}

Alchemist::Executable& Alchemist::Executable::operator<<(const std::string& str) {
	write(str);
	return *this;
}

Alchemist::Executable& Alchemist::Executable::operator<<(const Alchemist::Executable::_EoF&) {
	eof();
	return *this;
}

void Alchemist::Executable::run() {
	pipe(m_handle);
	m_pid = fork();

	if (m_pid == -1) throw std::runtime_error("Can not execute " + m_program);
	else if (m_pid == 0) {
		dup2(m_handle[0], STDIN_FILENO);
		dup2(m_handle[1], STDOUT_FILENO);
		::close(m_handle[0]);
		::close(m_handle[1]);

		std::string program_file = std::filesystem::path(m_program).filename().string();
		std::vector<char*> argv;
		argv.reserve(m_arguments.size() + 2);
		argv.push_back(program_file.data());
		for (size_t i = 0; i < m_arguments.size(); i++)
			argv.push_back(m_arguments[i].data());
		argv.push_back(NULL);
		
		/* ORIGINAL
		char *argv[] = {m_program.data(), NULL};
		if (execvp(argv[0], argv) < 0) exit(0); */
		execvp(m_program.data(), argv.data());
		exit(0);
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

void Alchemist::Executable::eof() {
	close(m_handle[1]);
	m_is_eof = true;
	if (m_redirected) m_redirected.value()->eof();
}

void Alchemist::Executable::close(int& fd) {
	::close(fd);
	fd = -1;
}
