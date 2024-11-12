#pragma once

#include <StormByte/system/process.hxx>

#include <memory>

namespace Alchemy::Process {
	class ALCHEMY_PRIVATE FFmpeg final: public StormByte::System::Process {
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