#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media::Metadata {
	class DLL_PUBLIC Subtitle {
		public:
			Subtitle(const std::string&);
			Subtitle(std::string&&) noexcept;
			Subtitle(const Subtitle&)					= default;
			Subtitle(Subtitle&&) noexcept				= default;
			Subtitle& operator=(const Subtitle&)		= default;
			Subtitle& operator=(Subtitle&&) noexcept	= default;
			~Subtitle() noexcept						= default;

			const std::string& GetEncoding() const noexcept;

		private:
			std::string m_encoding;
	};
}