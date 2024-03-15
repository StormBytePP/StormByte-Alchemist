#pragma once

#include "executable.hxx"

namespace Alchemist::System {
	class DLL_LOCAL FFmpeg final: public Executable {
		public:
			FFmpeg(const FFmpeg&)				= delete;
			FFmpeg(FFmpeg&&)					= default;
			FFmpeg& operator=(const FFmpeg&)	= delete;
			FFmpeg& operator=(FFmpeg&&)			= default;
			~FFmpeg()							= default;

			static FFmpeg hdr_plus(const std::filesystem::path&);

		private:
			FFmpeg(const std::filesystem::path&, std::vector<std::string>&&);
	};
}