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
		m_pstderr.close_read();
		m_pstderr.bind_write(STDERR_FILENO);

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

	m_pstdout.set_read_handle_information(HANDLE_FLAG_INHERIT, FALSE);
	m_pstderr.set_read_handle_information(HANDLE_FLAG_INHERIT, FALSE);
	m_pstdin.set_write_handle_information(HANDLE_FLAG_INHERIT, FALSE);

	std::wstring command = full_command();
	TCHAR* szCmdline = const_cast<TCHAR*>(command.c_str());

	if (CreateProcess(	NULL,
						szCmdline,			// command line 
						NULL,				// process security attributes 
						NULL,				// primary thread security attributes 
						TRUE,				// handles are inherited 
						CREATE_NO_WINDOW,	// creation flags 
						NULL,				// use parent's environment 
						NULL,				// use parent's current directory 
						&m_siStartInfo,		// STARTUPINFO pointer 
						&m_piProcInfo)) {
		// Set the rest of handles not inheritable by other execs
		m_pstdout.set_write_handle_information(HANDLE_FLAG_INHERIT, 0);
		m_pstderr.set_write_handle_information(HANDLE_FLAG_INHERIT, 0);
		m_pstdin.set_read_handle_information(HANDLE_FLAG_INHERIT, 0);
	
		// Close handles to the stdin and stdout pipes no longer needed by the child process.
		// If they are not explicitly closed, there is no way to recognize that the child process has ended.
		m_pstdout.close_write();
		m_pstderr.close_write();
		m_pstdin.close_read();
	}
	#endif
}

void Alchemist::System::Executable::send(const std::string& str) {
	m_pstdin << str;
}

#ifdef LINUX
int Alchemist::System::Executable::wait() {
	int status;
	if (m_forwarder)
		m_forwarder->join();
	waitpid(m_pid, &status, 0);
	return status;
}
#else
DWORD Alchemist::System::Executable::wait() {
	DWORD status;
	if (m_forwarder)
		m_forwarder->join();
	WaitForSingleObject(m_piProcInfo.hProcess, INFINITE);
	GetExitCodeThread(m_piProcInfo.hThread, &status);

	// Close handlers
	CloseHandle(m_piProcInfo.hProcess);
	CloseHandle(m_piProcInfo.hThread);
	return status;
}
#endif

#ifdef LINUX
void Alchemist::System::Executable::consume_and_forward(Executable& exec) {
	std::vector<char> buffer;
	ssize_t bytes_read, bytes_write;
	do {
		buffer.reserve(PIPE_BUF);
		m_pstdout.poll(100);
		exec.m_pstdin.poll(100);
		bytes_read = m_pstdout.read(buffer, PIPE_BUF);
		if (bytes_read > 0) {
			exec.m_pstdin.write(std::string(buffer.data(), bytes_read));
		}
	} while (!m_pstdout.has_read_event(POLLHUP) && !exec.m_pstdin.has_write_event(POLLHUP));
	exec.m_pstdin.close_write();
}
#else
void Alchemist::System::Executable::consume_and_forward(Executable& exec) {
	DWORD status;
	do {
		std::optional<std::string> buffer;
		m_pstdout >> buffer;
		if (buffer) exec.m_pstdin << *buffer;
		status = WaitForSingleObject(m_piProcInfo.hProcess, 100);
	} while (status != WAIT_OBJECT_0);
	exec.m_pstdin.close_write();
}
#endif

#ifdef WINDOWS
std::wstring Alchemist::System::Executable::full_command() const {
	std::stringstream ss;

	std::vector<std::string> full = { m_program };
	full.insert(full.end(), m_arguments.begin(), m_arguments.end());
	std::copy(full.begin(), full.end(), std::ostream_iterator<std::string>(ss, " "));
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, ss.str().c_str(), -1, NULL, 0);
	std::unique_ptr<wchar_t[]> wstr_buff = std::make_unique<wchar_t[]>(wchars_num);
	MultiByteToWideChar(CP_UTF8, 0, ss.str().c_str(), -1, wstr_buff.get(), wchars_num);
	return std::wstring(wstr_buff.get(), wchars_num);
}
#endif