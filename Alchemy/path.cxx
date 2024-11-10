#include <Alchemy/path.hxx>

#ifdef LINUX
#include <pwd.h>
#include <regex>
#include <sys/types.h>
#include <unistd.h>
#else
#include <windows.h>
#include <tchar.h>
#define INFO_BUFFER_SIZE 32767
#endif

using namespace Alchemy;

const std::filesystem::path Path::Home() {
	#ifdef LINUX
	const struct passwd *pw = getpwuid(getuid());
	return std::filesystem::path(pw->pw_dir);
	#else
	return std::filesystem::path(ExpandEnvironmentVariable(TEXT("%PROGRAMDATA%")));
	#endif
}

const std::filesystem::path Path::Conf() {
	#ifdef LINUX
	return Home() / ".alchemist";
	#else
	return Home() / "Alchemist";
	#endif
}

const std::filesystem::path Path::Expand(const std::string& path) {
	return ExpandEnvironmentVariable(path);
} 

#ifdef WINDOWS
const std::filesystem::path Path::Expand(const std::wstring& path) {
	return ExpandEnvironmentVariable(path);
} 
#endif

const std::string Path::ExpandEnvironmentVariable(const std::string& var) {
	#ifdef WINDOWS
	return ExpandEnvironmentVariable(UTF8Decode(var));
	#else
	return std::regex_replace(var, std::regex("~"), Home().string());
	#endif
}
#ifdef WINDOWS
const std::string Path::ExpandEnvironmentVariable(const std::wstring& var) {
	TCHAR  infoBuf[INFO_BUFFER_SIZE] = { '\0' };
	::ExpandEnvironmentStrings(var.c_str(), infoBuf, INFO_BUFFER_SIZE);

	return UTF8Encode(infoBuf);
}

std::string Path::UTF8Encode(const std::wstring& wstr) {
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

std::wstring Path::UTF8Decode(const std::string& str) {
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}
#endif