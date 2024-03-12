#include "pipe.hxx"

#include <fcntl.h>
#include <io.h>

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
	return *this;
}

std::optional<std::string>& Alchemist::System::Windows::Pipe::operator>>(std::optional<std::string>& out) const {
	return out;
}

void Alchemist::System::Windows::Pipe::write(const std::string& str) {
	_write(m_fd[1], str.c_str(), sizeof(char) * static_cast<unsigned int>(str.length()));
}
#include <iostream>
std::optional<std::string> Alchemist::System::Windows::Pipe::read() const {
	std::optional<std::string> result;
	std::string data = "";
	int bytes;
	do {
		char buffer[MAX_BYTES];
		bytes = _read(m_fd[0], buffer, MAX_BYTES);
		if (bytes > 0)
			data += std::string(buffer, bytes);
		std::terminate();
	} while (bytes > 0);
	if (!data.empty())
		result = data;
	return result;
}

void Alchemist::System::Windows::Pipe::bind(int& src, int dest) {
}

void Alchemist::System::Windows::Pipe::close(int& fd) {
	_close(fd);
}

void Alchemist::System::Windows::Pipe::init() {
	_pipe(m_fd, MAX_BYTES, O_BINARY);
}
