#pragma once

#include "../container.hxx"

namespace Alchemist::Media::Container {
	class DLL_PUBLIC AVI final: public Base {
		public:
			AVI(const std::filesystem::path&);
			AVI(std::filesystem::path&&);
			AVI(const AVI&)						= default;
			AVI(AVI&&) noexcept					= default;
			AVI& operator=(const AVI&)			= default;
			AVI& operator=(AVI&&) noexcept		= default;
			~AVI() noexcept						= default;

			std::list<Codec::Type> get_supported_codecs() const;
	};
}