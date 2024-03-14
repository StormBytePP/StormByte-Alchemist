#include "pipe.hxx"

#ifdef LINUX
#include <fcntl.h>
#include <unistd.h>
#else
SECURITY_ATTRIBUTES Alchemist::System::Pipe::m_sAttr = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
#endif
#include <vector>

Alchemist::System::Pipe::Pipe() {
	#ifdef LINUX
	pipe2(m_fd, O_CLOEXEC);
	#else
	CreatePipe(&m_fd[0], &m_fd[1], &m_sAttr, 0);
	#endif
}

Alchemist::System::Pipe::~Pipe() {
	close_read();
	close_write();
}

#ifdef LINUX
void Alchemist::System::Pipe::bind_read(int dest) {
	bind(m_fd[0], dest);
}

void Alchemist::System::Pipe::bind_write(int dest) {
	bind(m_fd[1], dest);
}

ssize_t Alchemist::System::Pipe::write(const std::string& data) {
	return ::write(m_fd[1], data.c_str(), sizeof(char) * data.length());
}

bool Alchemist::System::Pipe::write_eof() const {
	pollfd poll_data;
	poll_data.fd = m_fd[1];
	poll_data.events = POLLOUT;
	poll(&poll_data, 1, -1);

	return !((poll_data.revents & POLLOUT) == POLLOUT) || ((poll_data.revents & POLLERR) == POLLERR);
}

ssize_t Alchemist::System::Pipe::read(std::vector<char>& buffer, ssize_t bytes) const {
	return ::read(m_fd[0], &buffer[0], bytes);
}

bool Alchemist::System::Pipe::read_eof() const {
	pollfd poll_data;
	poll_data.fd = m_fd[0];
	poll_data.events = POLLIN;
	poll(&poll_data, 1, -1);

	return ((poll_data.revents & POLLHUP) == POLLHUP) || ((poll_data.revents & POLLERR) == POLLERR);
}
#else
void Alchemist::System::Pipe::set_read_handle_information(DWORD mask, DWORD flags) {
	set_handle_information(m_fd[0], mask, flags);
}

void Alchemist::System::Pipe::set_write_handle_information(DWORD mask, DWORD flags) {
	set_handle_information(m_fd[1], mask, flags);
}

HANDLE Alchemist::System::Pipe::get_read_handle() const {
	return m_fd[0];
}

HANDLE Alchemist::System::Pipe::get_write_handle() const {
	return m_fd[1];
}

DWORD Alchemist::System::Pipe::write(const std::string& data) {
	DWORD dwWritten;
	WriteFile(m_fd[1], data.c_str(), static_cast<DWORD>(sizeof(char) * data.length()), &dwWritten, NULL);
	return dwWritten;
}

DWORD Alchemist::System::Pipe::read(std::vector<CHAR>& buffer, DWORD size) const {
	DWORD dwRead;
	ReadFile(m_fd[0], buffer.data(), size, &dwRead, NULL);
	return dwRead;
}
#endif

/** This function will write chunks until write HUPs taking ownership    **/
/** of the provided data to write. Empty parameter is Undefined Behavior **/
#ifdef LINUX
bool Alchemist::System::Pipe::write_atomic(std::string&& data) {
	std::string out = std::move(data);
	bool can_continue;

	do {
		size_t chunk_size = (out.length() > PIPE_BUF) ? PIPE_BUF : out.length(), bytes_written = 0;
		bytes_written = ::write(m_fd[1], out.c_str(), chunk_size);
		out.erase(0, chunk_size);
		can_continue = (chunk_size == bytes_written) && !write_eof();
	} while (!out.empty() && can_continue);
	return out.empty();
}
#else
bool Alchemist::System::Pipe::write_atomic(std::string&& data) {
	std::string out = std::move(data);
	bool can_continue;

	do {
		size_t chunk_size = (out.length() > 4096) ? 4096 : out.length(), bytes_written = 0;
		DWORD dwWritten;
		WriteFile(m_fd[1], out.c_str(), static_cast<DWORD>(chunk_size), &dwWritten, NULL);
		out.erase(0, chunk_size);
		can_continue = chunk_size == dwWritten;
	} while (!out.empty() && can_continue);
	return out.empty();
}
#endif

void Alchemist::System::Pipe::close_read() {
	close(m_fd[0]);
}

void Alchemist::System::Pipe::close_write() {
	close(m_fd[1]);
}

Alchemist::System::Pipe& Alchemist::System::Pipe::operator<<(const std::string& data) {
	write(data);
	return *this;
}

std::optional<std::string>& Alchemist::System::Pipe::operator>>(std::optional<std::string>& out) const {
	#ifdef LINUX
	ssize_t bytes;
	#else
	DWORD bytes;
	#endif
	std::vector<char> buffer(MAX_READ_BYTES);
	while((bytes = read(buffer, MAX_READ_BYTES))) {
		if (bytes > 0) {
			if (out)
				out = *out + std::string(&buffer[0], bytes);
			else
				out = std::string(&buffer[0], bytes);
		}
	}
	return out;
}

#ifdef LINUX
void Alchemist::System::Pipe::bind(int& src, int dest) {
	dup2(src, dest);
	close(src);
}

void Alchemist::System::Pipe::close(int& fd) {
	::close(fd);
}
#else
void Alchemist::System::Pipe::close(HANDLE& fd) {
	CloseHandle(fd);
}

void Alchemist::System::Pipe::set_handle_information(HANDLE handle, DWORD mask, DWORD flags) {
	SetHandleInformation(handle, mask, flags);
}
#endif

