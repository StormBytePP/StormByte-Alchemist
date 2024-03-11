#include "executable.hxx"

#include <filesystem>

Alchemist::System::Windows::Executable::Executable(const std::string& prog, const std::vector<std::string>& args):m_program(prog), m_arguments(args) {
	run();
}

Alchemist::System::Windows::Executable::Executable(std::string&& prog, std::vector<std::string>&& args):m_program(std::move(prog)), m_arguments(std::move(args)) {
	run();
}

Alchemist::System::Windows::Executable& Alchemist::System::Windows::Executable::operator>>(Executable& exe) {
	return exe;
}

std::optional<std::string>& Alchemist::System::Windows::Executable::operator>>(std::optional<std::string>& data) {
	return data;
}

std::ostream& Alchemist::System::Windows::operator<<(std::ostream& os, const Windows::Executable& exe) {
	return os;
}

Alchemist::System::Windows::Executable& Alchemist::System::Windows::Executable::operator<<(const std::string& data) {
	return *this;
}

void Alchemist::System::Windows::Executable::operator<<(const System::Executable::_EoF&) {
}

void Alchemist::System::Windows::Executable::run() {
}

void Alchemist::System::Windows::Executable::write(const std::string& str) {
	m_pstdin << str;
}

int Alchemist::System::Windows::Executable::wait() {
	return -1;
}

void Alchemist::System::Windows::Executable::consume_and_forward(Executable& exec) {
}
