#include "pipe.hxx"

SECURITY_ATTRIBUTES Alchemist::System::Windows::Pipe::m_sAttr = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

Alchemist::System::Windows::Pipe::Pipe() {
	init();
}

Alchemist::System::Windows::Pipe::~Pipe() {
	close_read();
	close_write();
}

void Alchemist::System::Windows::Pipe::bind_read(int dest) {
	//bind(m_fd[0], dest);
}

void Alchemist::System::Windows::Pipe::bind_write(int dest) {
	//bind(m_fd[1], dest);
}

void Alchemist::System::Windows::Pipe::close_read() {
	close(m_fd[0]);
}

void Alchemist::System::Windows::Pipe::close_write() {
	close(m_fd[1]);
}

int Alchemist::System::Windows::Pipe::poll(int timeout) const {
	return -1;
}

bool Alchemist::System::Windows::Pipe::has_read_event(unsigned short event) const {
	return false;
}

bool Alchemist::System::Windows::Pipe::has_write_event(unsigned short event) const {
	return false;
}

Alchemist::System::Windows::Pipe& Alchemist::System::Windows::Pipe::operator<<(const std::string& data) {
	write(data);
	return *this;
}

std::optional<std::string>& Alchemist::System::Windows::Pipe::operator>>(std::optional<std::string>& out) const {
	std::optional<std::string> data = read();
	if (data) {
		if (out)
			out = *out + *data;
		else
			out = *data;
	}
	return out;
}

void Alchemist::System::Windows::Pipe::write(const std::string& str) {
	DWORD dwWritten;
	WriteFile(m_fd[1], str.c_str(), static_cast<DWORD>(sizeof(char) * str.length()), &dwWritten, NULL);
}

std::optional<std::string> Alchemist::System::Windows::Pipe::read() const {
	std::optional<std::string> result;
	std::string data = "";
	DWORD dwRead;
	CHAR buffer[MAX_BYTES];
	do {
	
		auto res = ReadFile(m_fd[0], buffer, 10, &dwRead, NULL);
		if (dwRead > 0) data += std::string(buffer, dwRead);
	} while (dwRead > 0);
	if (!data.empty()) result = data;
	return result;
}

void Alchemist::System::Windows::Pipe::bind(int& src, int dest) {
}

void Alchemist::System::Windows::Pipe::close(HANDLE& fd) {
	CloseHandle(fd);
}

void Alchemist::System::Windows::Pipe::init() {
	CreatePipe(&m_fd[0], &m_fd[1], &m_sAttr, 0);
}
