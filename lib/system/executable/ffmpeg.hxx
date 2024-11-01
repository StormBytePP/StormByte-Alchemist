#pragma once

#include "../executable.hxx"

#include <memory>

namespace Alchemist::System {
	class ALCHEMY_PRIVATE FFmpeg final: public Executable {
		public:
			FFmpeg(const FFmpeg&)				= delete;
			FFmpeg(FFmpeg&&)					= delete;
			FFmpeg& operator=(const FFmpeg&)	= delete;
			FFmpeg& operator=(FFmpeg&&)			= delete;
			~FFmpeg() noexcept					= default;

			static std::unique_ptr<FFmpeg> hdr_stream(const std::filesystem::path&);

		private:
			FFmpeg(const std::filesystem::path&, std::vector<std::string>&&);
	};
}