#pragma once

#include "../executable.hxx"

#include <memory>

namespace Alchemist::System {
	class DLL_LOCAL FFmpeg final: public Executable {
		public:
			FFmpeg(const FFmpeg&)				= delete;
			FFmpeg(FFmpeg&&)					= delete;
			FFmpeg& operator=(const FFmpeg&)	= delete;
			FFmpeg& operator=(FFmpeg&&)			= delete;

			static std::unique_ptr<FFmpeg> hdr_plus(const std::filesystem::path&);

		private:
			FFmpeg(const std::filesystem::path&, std::vector<std::string>&&);
	};
}