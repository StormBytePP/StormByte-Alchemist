#pragma once

#include "../executable.hxx"

#include <memory>

namespace Alchemist::System {
	class DLL_LOCAL HDR10Plus final: public Executable {
		public:
			HDR10Plus(const HDR10Plus&)				= delete;
			HDR10Plus(HDR10Plus&&)					= delete;
			HDR10Plus& operator=(const HDR10Plus&)	= delete;
			HDR10Plus& operator=(HDR10Plus&&)		= delete;
			~HDR10Plus()							= default;

			static std::unique_ptr<HDR10Plus> hdr_plus_detect();

		private:
			HDR10Plus(const std::filesystem::path&, std::vector<std::string>&&);
	};
}