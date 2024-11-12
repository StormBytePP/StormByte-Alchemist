#pragma once

#include <StormByte/system/process.hxx>

#include <memory>

namespace Alchemy::Process {
	class ALCHEMY_PRIVATE HDR10Plus final: public StormByte::System::Process {
		public:
			HDR10Plus(const HDR10Plus&)				= delete;
			HDR10Plus(HDR10Plus&&)					= delete;
			HDR10Plus& operator=(const HDR10Plus&)	= delete;
			HDR10Plus& operator=(HDR10Plus&&)		= delete;
			~HDR10Plus() noexcept					= default;

			static std::unique_ptr<HDR10Plus> hdr_plus_detect();

		private:
			HDR10Plus(const std::filesystem::path&, std::vector<std::string>&&);
	};
}