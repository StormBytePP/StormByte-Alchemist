#include <Alchemy/path.hxx>
#include <StormByte/system/variable.hxx>

using namespace Alchemy;
using namespace StormByte;

const std::filesystem::path Path::Home() {
	#ifdef LINUX
	return System::Variable::Expand("~");
	#else
	return System::Variable::Expand("%PROGRAMDATA%");
	#endif
}

const std::filesystem::path Path::Conf() {
	#ifdef LINUX
	return Home() / ".alchemist";
	#else
	return Home() / "Alchemist";
	#endif
}
