#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>

int main() {
	std::string program = "cmd.exe";
	std::vector<std::string> args = { "/c", "ipconfig" };
	std::stringstream ss;

	std::vector<std::string> full = { program };
	full.insert(full.end(), args.begin(), args.end());
	std::copy(full.begin(), full.end(), std::ostream_iterator<std::string>(ss, " "));
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, ss.str().c_str(), -1, NULL, 0);
	std::unique_ptr<wchar_t[]> wstr_buff = std::make_unique<wchar_t[]>(wchars_num);
	MultiByteToWideChar(CP_UTF8, 0, ss.str().c_str(), -1, wstr_buff.get(), wchars_num);
	std::wstring wstr = std::wstring(wstr_buff.get(), wchars_num);
	TCHAR* fuck = const_cast<TCHAR*>(wstr.c_str());

	std::wcout << "The result is: '" << wstr << "'" << std::endl;
	std::wcout << "The result is: '" << fuck << "'" << std::endl;
}