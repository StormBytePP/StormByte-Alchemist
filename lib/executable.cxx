#include "executable.hxx"

#include <filesystem>
#include <sys/wait.h>

Alchemist::Executable::Executable(const std::string& prog, const std::vector<std::string>& args):m_program(prog), m_arguments(args) {
	run();
}

Alchemist::Executable::Executable(std::string&& prog, std::vector<std::string>&& args):m_program(std::move(prog)), m_arguments(std::move(args)) {
	run();
}

Alchemist::Executable& Alchemist::Executable::operator>>(Executable& exe) {
	m_syncer=std::thread(&Alchemist::Executable::consume_and_redirect, this, &exe);
	return exe;
}

std::string& Alchemist::Executable::operator>>(std::string& str) {
	auto data = read_stdout();
	if (data) str += *data;
	return str;
}

std::ostream& DLL_PUBLIC Alchemist::operator<<(std::ostream& os, const Executable& exe) {
	auto data = exe.read_stdout();
	if (data) os << *data;
	return os;
}

Alchemist::Executable& Alchemist::Executable::operator<<(const std::string& data) {
	write(data);
	return *this;
}

void Alchemist::Executable::operator<<(const _EoF&) {
	close(m_pstdin[1]);
}

void Alchemist::Executable::run() {
	pipe(m_pstdin);
	pipe(m_pstdout);
	pipe(m_pstderr);

	m_pid = fork();

	if (m_pid == 0) {
		/* STDIN: Child reads from STDIN but does not write to */
		close(m_pstdin[1]);
		dup2(m_pstdin[0], STDIN_FILENO);
		close(m_pstdin[0]);

		/* STDOUT: Child writes to STDOUT but does not read from */
		close(m_pstdout[0]);
		dup2(m_pstdout[1], STDOUT_FILENO);
		close(m_pstdout[1]);

		/* STDERR: Child writes to STDERR but does not read from */
		close(m_pstderr[0]);
		dup2(m_pstderr[1], STDERR_FILENO);
		close(m_pstderr[1]);

		std::string program_file = std::filesystem::path(m_program).filename().string();
		std::vector<char*> argv;
		argv.reserve(m_arguments.size() + 2);
		argv.push_back(program_file.data());
		for (size_t i = 0; i < m_arguments.size(); i++)
			argv.push_back(m_arguments[i].data());
		argv.push_back(NULL);
		
		execvp(m_program.data(), argv.data());
		// If we reach here then we failed to execute the program
		exit(0);
	}
	else {
		/* STDIN: Parent writes to STDIN but does not read from */
		close(m_pstdin[0]);

		/* STDOUT: Parent reads from to STDOUT but does not write to */
		close(m_pstdout[1]);

		/* STDERR: Parent reads from to STDERR but does not write to */
		close(m_pstderr[1]);
	}
}

void Alchemist::Executable::write(const std::string& str) {
	::write(m_pstdin[1], str.c_str(), sizeof(str.get_allocator()) * str.length());
}

std::optional<std::string> Alchemist::Executable::read_stdout() const {
	return read(m_pstdout[0]);
}

std::optional<std::string> Alchemist::Executable::read_stderr() const {
	return read(m_pstderr[0]);
}

std::optional<std::string> Alchemist::Executable::read(int handle) const {
	std::optional<std::string> result;
	char buffer[BUFFER_SIZE];
	ssize_t bytes;
	std::string data = "";
	while ((bytes = ::read(handle, buffer, BUFFER_SIZE)) > 0) {
		data += std::string(buffer, bytes);
	};
	if (!data.empty()) result = std::move(data);
	return result;
}

int Alchemist::Executable::wait() {
	int status;
	waitpid(m_pid, &status, 0);
	if (m_syncer) {
		m_syncer.value().join();
		m_syncer.reset();
	}
	return status;
}

void Alchemist::Executable::consume_and_redirect(Executable* exec) {
	std::optional<std::string> data;
	while((data = read_stdout())) {
		exec->write(*data);
	}
	close(exec->m_pstdin[1]);
}
