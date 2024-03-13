#include "executable.hxx"

#include <filesystem>
#ifdef LINUX
#include <sys/wait.h>
#endif

Alchemist::System::Executable::Executable(const std::string& prog, const std::vector<std::string>& args):m_program(prog), m_arguments(args) {
	run();
}

Alchemist::System::Executable::Executable(std::string&& prog, std::vector<std::string>&& args):m_program(std::move(prog)), m_arguments(std::move(args)) {
	run();
}

Alchemist::System::Executable& Alchemist::System::Executable::operator>>(Executable& exe) {
	m_forwarder.reset(new std::thread(&Alchemist::System::Executable::consume_and_forward, this, std::ref(exe)));
	return exe;
}

std::optional<std::string>& Alchemist::System::Executable::operator>>(std::optional<std::string>& data) {
	m_pstdout >> data;
	return data;
}

std::ostream& Alchemist::System::operator<<(std::ostream& os, const Executable& exe) {
	std::optional<std::string> data;
	exe.m_pstdout >> data;
	if (data) os << *data;
	return os;
}

Alchemist::System::Executable& Alchemist::System::Executable::operator<<(const std::string& data) {
	m_pstdin << data;
	return *this;
}

void Alchemist::System::Executable::operator<<(const System::_EoF&) {
	m_pstdin.close_write();
}

void Alchemist::System::Executable::run() {
	#ifdef LINUX
	m_pid = fork();

	if (m_pid == 0) {
		/* STDIN: Child reads from STDIN but does not write to */
		m_pstdin.close_write();
		m_pstdin.bind_read(STDIN_FILENO);

		/* STDOUT: Child writes to STDOUT but does not read from */
		m_pstdout.close_read();
		m_pstdout.bind_write(STDOUT_FILENO);

		/* STDERR: Child writes to STDERR but does not read from */
		m_pstdout.close_read();
		m_pstdout.bind_write(STDERR_FILENO);

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
		m_pstdin.close_read();

		/* STDOUT: Parent reads from to STDOUT but does not write to */
		m_pstdout.close_write();

		/* STDERR: Parent reads from to STDERR but does not write to */
		m_pstderr.close_write();
	}
	#else
	ZeroMemory(&m_piProcInfo,	sizeof(PROCESS_INFORMATION));
	ZeroMemory(&m_siStartInfo,	sizeof(STARTUPINFO));
	m_siStartInfo.cb = sizeof(STARTUPINFO);
	m_siStartInfo.hStdError = m_pstderr.get_write_handle();
	m_siStartInfo.hStdOutput = m_pstdout.get_write_handle();
	m_siStartInfo.hStdInput = m_pstdin.get_read_handle();
	m_siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	m_pstdout.set_read_handle_information(HANDLE_FLAG_INHERIT, 0);
	m_pstderr.set_read_handle_information(HANDLE_FLAG_INHERIT, 0);
	m_pstdin.set_write_handle_information(HANDLE_FLAG_INHERIT, 0);

	//std::cout << "The result is: '" << s.str() << "'" << std::endl;

	//if (CreateProcess(	NULL,
	//					szCmdline,     // command line 
	//					NULL,          // process security attributes 
	//					NULL,          // primary thread security attributes 
	//					TRUE,          // handles are inherited 
	//					0,             // creation flags 
	//					NULL,          // use parent's environment 
	//					NULL,          // use parent's current directory 
	//					&siStartInfo,  // STARTUPINFO pointer 
	//					&piProcInfo)) {
	//	// Close handles to the child process and its primary thread.
	//	// Some applications might keep these handles to monitor the status
	//	// of the child process, for example. 
	//	CloseHandle(piProcInfo.hProcess);
	//	CloseHandle(piProcInfo.hThread);
	//
	//	// Close handles to the stdin and stdout pipes no longer needed by the child process.
	//	// If they are not explicitly closed, there is no way to recognize that the child process has ended.
	//	m_pstdout.close_write();
	//	m_pstdin.close_read();
	//}
	#endif
}

void Alchemist::System::Executable::send(const std::string& str) {
	m_pstdin << str;
}

int Alchemist::System::Executable::wait() {
	int status = 0;
	if (m_forwarder)
		m_forwarder->join();
	#ifdef LINUX
	waitpid(m_pid, &status, 0);
	#else
	WaitForSingleObject(m_piProcInfo.hProcess, INFINITE);
	#endif
	return status;
}

void Alchemist::System::Executable::consume_and_forward(Executable& exec) {
	#ifdef LINUX
	do {
		std::optional<std::string> buffer;
		m_pstdout.poll(100);
		m_pstdout >> buffer;
		if (buffer)
			exec.m_pstdin << *buffer;
	} while (!m_pstdout.has_read_event(POLLHUP));
	#endif
	exec.m_pstdin.close_write();
}
