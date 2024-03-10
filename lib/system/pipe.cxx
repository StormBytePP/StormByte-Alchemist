#include "pipe.hxx"

#include <unistd.h>

Alchemist::System::Pipe::Pipe() {
	pipe(m_fd);
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
	::write(m_fd[1], str.c_str(), sizeof(str.get_allocator()) * str.length());
}

std::optional<std::string> Alchemist::System::Pipe::read() const {
	std::optional<std::string> result;
	char buffer[MAX_BYTES];
	ssize_t bytes;
	std::string data = "";
	while ((bytes = ::read(m_fd[0], buffer, MAX_BYTES)) >= 0) {
		data += std::string(buffer, bytes);
	};
	if (!data.empty()) {
		result = std::move(data);
	}
	return result;
}

void Alchemist::System::Pipe::bind(int& src, int dest) {
	dup2(src, dest);
	close(src); // Here maybe use ::close instead
}

void Alchemist::System::Pipe::close(int& fd) {
	if (fd != -1) {
		::close(fd);
		fd = -1;
	}
}