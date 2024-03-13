#include "pipe.hxx"

#ifdef LINUX
#include <fcntl.h>
#include <unistd.h>
#else
SECURITY_ATTRIBUTES Alchemist::System::Windows::Pipe::m_sAttr = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
#endif

Alchemist::System::Pipe::Pipe() {
	init();
}

Alchemist::System::Pipe::~Pipe() {
	close_read();
	close_write();
}

void Alchemist::System::Pipe::bind_read(int dest) {
	bind(m_fd[0], dest);
}

void Alchemist::System::Pipe::bind_write(int dest) {
	bind(m_fd[1], dest);
}

void Alchemist::System::Pipe::close_read() {
	close(m_fd[0]);
}

void Alchemist::System::Pipe::close_write() {
	close(m_fd[1]);
}

#ifdef LINUX
int Alchemist::System::Pipe::poll(int timeout) const {
	return ::poll(m_fd_data, 2, timeout);
}

bool Alchemist::System::Pipe::has_read_event(unsigned short event) const {
	return (m_fd_data[0].revents & event) == event;
}

bool Alchemist::System::Pipe::has_write_event(unsigned short event) const {
	return (m_fd_data[1].revents & event) == event;
}
#endif

Alchemist::System::Pipe& Alchemist::System::Pipe::operator<<(const std::string& data) {
	write(data);
	return *this;
}

std::optional<std::string>& Alchemist::System::Pipe::operator>>(std::optional<std::string>& out) const {
	std::optional<std::string> data = read();
	if (data) {
		if (out)
			out = *out + *data;
		else
			out = *data;
	}
	return out;
}

void Alchemist::System::Pipe::write(const std::string& str) {
	#ifdef LINUX
	bool retry = true;
	do {
		poll(100);
		if (has_write_event(POLLHUP)) {
			retry = false;
		}
		else if (has_write_event(POLLOUT)) {
			::write(m_fd[1], str.c_str(), sizeof(char) * str.length());
			retry = false;
		}
	} while (retry);
	#else
	DWORD dwWritten;
	WriteFile(m_fd[1], str.c_str(), static_cast<DWORD>(sizeof(char) * str.length()), &dwWritten, NULL);
	#endif
}

std::optional<std::string> Alchemist::System::Pipe::read() const {
	std::optional<std::string> result;
	std::string data = "";
	#ifdef LINUX
	bool retry = true;
	do {
		poll(100);
		ssize_t bytes;
		if (has_read_event(POLLIN)) {
			char buffer[MAX_BYTES];
			while ((bytes = ::read(m_fd[0], buffer, MAX_BYTES)) > 0) {
				data += std::string(buffer, bytes);
			};
			retry = false;
		}
		else if (has_read_event(POLLHUP)) {
			retry = false;
		}
	} while(retry);
	#else
	DWORD dwRead;
	CHAR buffer[MAX_BYTES];
	do {
	
		auto res = ReadFile(m_fd[0], buffer, 10, &dwRead, NULL);
		if (dwRead > 0) data += std::string(buffer, dwRead);
	} while (dwRead > 0);
	#endif
	if (!data.empty()) result = std::move(data);
	return result;
}

#ifdef LINUX
void Alchemist::System::Pipe::bind(int& src, int dest) {
	dup2(src, dest);
	close(src);
}
#endif

void Alchemist::System::Pipe::close(int& fd) {
	#ifdef LINUX
	::close(fd);
	#else
	CloseHandle(fd);
	#endif
}

void Alchemist::System::Pipe::init() {
	#ifdef LINUX
	pipe2(m_fd, O_CLOEXEC);
	m_fd_data[0].fd = m_fd[0];
	m_fd_data[0].events = POLLIN;
	m_fd_data[0].revents = 0;
	m_fd_data[1].fd = m_fd[1];
	m_fd_data[1].events = POLLOUT;
	m_fd_data[1].revents = 0;
	#else
	CreatePipe(&m_fd[0], &m_fd[1], &m_sAttr, 0);
	#endif
}
