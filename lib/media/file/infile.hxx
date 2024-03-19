#pragma once

#include "base.hxx"

namespace Alchemist::Media::File {
	class DLL_PUBLIC InFile final: public Base {
		public:
			InFile(const std::filesystem::path&);
			InFile(std::filesystem::path&&);

		private:
			void update() override;
			void update_readability();
			void update_features();
			void update_streams();
	};
}