#if defined _WIN32 || defined __CYGWIN__
	#include "windows/executable.hxx"
#else
	#include "linux/executable.hxx"
#endif

Alchemist::System::Executable::Executable(const std::string& prog, const std::vector<std::string>& args) {
	m_exec_impl = std::make_unique<ExecImpl>(prog, args);
}

Alchemist::System::Executable::Executable(std::string&& prog, std::vector<std::string>&& args) {
	m_exec_impl = std::make_unique<ExecImpl>(std::move(prog), std::move(args));
}

Alchemist::System::Executable::~Executable() {
	m_exec_impl.release();
}

int Alchemist::System::Executable::wait() {
	return m_exec_impl->wait();
}

Alchemist::System::Executable& Alchemist::System::Executable::operator>>(Executable& exe) {
	m_exec_impl->operator>>(*exe.m_exec_impl);
	return exe;
}

std::optional<std::string>& Alchemist::System::Executable::operator>>(std::optional<std::string>& data) {
	m_exec_impl->operator>>(data);
	return data;
}

std::ostream& DLL_PUBLIC Alchemist::System::operator<<(std::ostream& os, const System::Executable& exe) {
	return operator<<(os, *exe.m_exec_impl);
}

Alchemist::System::Executable& Alchemist::System::Executable::operator<<(const std::string& data) {
	m_exec_impl->operator<<(data);
	return *this;
}

void Alchemist::System::Executable::operator<<(const _EoF& _eof) {
	m_exec_impl->operator<<(_eof);
}
