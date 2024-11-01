#include <Alchemy/info.hxx>
#include "generated/definitions.h"

#ifdef WINDOWS
#include <windows.h>
#endif

const std::string Alchemist::Info::Name 	= LIBRARY_NAME;
const std::string Alchemist::Info::Author 	= LIBRARY_AUTHOR;
const std::string Alchemist::Info::Version 	= LIBRARY_VERSION;
const std::string Alchemist::Info::URI 		= PROJECT_URI;

const std::filesystem::path Alchemist::Info::ffmpeg_path() {
	return prefix() / FFMPEG_PATH;
}

const std::filesystem::path Alchemist::Info::ffprobe_path() {
	return prefix() / FFPROBE_PATH;
}

const std::filesystem::path Alchemist::Info::hdr10plus_tool_path() {
	return prefix() / HDR10PLUS_TOOL_PATH;
}

const std::filesystem::path Alchemist::Info::prefix() {
	#ifdef WINDOWS
	TCHAR ownPth[MAX_PATH]; 

	// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL) {
		// Use GetModuleFileName() with module handle to get the path
		GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));
		return std::filesystem::path(ownPth).remove_filename();
	}
	#endif
	return std::filesystem::path();
}
