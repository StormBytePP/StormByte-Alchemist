#include "info.hxx"
#include "generated/path.h"
#include "generated/version.h"

#ifdef WINDOWS
#include <windows.h>
#endif

const std::string Alchemist::Info::Name 	= LIBRARY_NAME;
const std::string Alchemist::Info::Author 	= LIBRARY_AUTHOR;
const std::string Alchemist::Info::Version 	= LIBRARY_VERSION;
const std::string Alchemist::Info::URI 		= PROJECT_URI;

const std::filesystem::path Alchemist::Info::ffmpeg_path() {
	#ifdef WINDOWS
	return current_path() / "bin" / std::filesystem::path("ffmpeg.exe");
	#else
	return FFMPEG_PATH;
	#endif
}

const std::filesystem::path Alchemist::Info::ffprobe_path() {
	#ifdef WINDOWS
	return current_path() / "bin" / std::filesystem::path("ffprobe.exe");
	#else
	return FFPROBE_PATH;
	#endif
}

#ifdef _WIN32
const std::filesystem::path Alchemist::Info::current_path() {
	TCHAR ownPth[MAX_PATH]; 

	// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL) {
		// Use GetModuleFileName() with module handle to get the path
		GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));
		return std::filesystem::path(ownPth).remove_filename();
	}
	else
		return std::filesystem::path();
}
#endif