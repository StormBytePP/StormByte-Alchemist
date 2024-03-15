#pragma once

#include "executable.hxx"

namespace Alchemist::System {
	class DLL_LOCAL HDR10Plus final: public Executable {
		public:
			HDR10Plus(const HDR10Plus&)				= delete;
			HDR10Plus(HDR10Plus&&)					= default;
			HDR10Plus& operator=(const HDR10Plus&)	= delete;
			HDR10Plus& operator=(HDR10Plus&&)		= default;
			~HDR10Plus()							= default;

			static HDR10Plus hdr_plus_detect(); // No parameter as it reads stdin

		private:
			HDR10Plus(const std::filesystem::path&, std::vector<std::string>&&);
	};
}