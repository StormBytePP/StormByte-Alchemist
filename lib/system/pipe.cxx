#include "pipe.hxx"

Alchemist::System::Pipe::Pipe() {
	m_pipe_impl = std::make_unique<PipeImpl>();
}

Alchemist::System::Pipe::~Pipe() {
	m_pipe_impl.release();
}

void Alchemist::System::Pipe::bind_read(int dest) {
	m_pipe_impl->bind_read(dest);
}

void Alchemist::System::Pipe::bind_write(int dest) {
	m_pipe_impl->bind_write(dest);
}

void Alchemist::System::Pipe::close_read() {
	m_pipe_impl->close_read();
}

void Alchemist::System::Pipe::close_write() {
	m_pipe_impl->close_write();
}

int Alchemist::System::Pipe::poll(int timeout) const {
	return m_pipe_impl->poll(timeout);
}

bool Alchemist::System::Pipe::has_read_event(unsigned short event) const {
	return m_pipe_impl->has_read_event(event);
}

bool Alchemist::System::Pipe::has_write_event(unsigned short event) const {
	return m_pipe_impl->has_write_event(event);
}
#include <iostream>
Alchemist::System::Pipe& Alchemist::System::Pipe::operator<<(const std::string& data) {
	m_pipe_impl->operator<<(data);
	return *this;
}

std::optional<std::string>& Alchemist::System::Pipe::operator>>(std::optional<std::string>& out) const {
	return m_pipe_impl->operator>>(out);
}
