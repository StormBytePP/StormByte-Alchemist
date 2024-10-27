#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media::Subtitle {
	class DLL_PUBLIC Metadata {
		public:
			Metadata(const std::string&);
			Metadata(std::string&&) noexcept;
			Metadata(const Metadata&)					= default;
			Metadata(Metadata&&) noexcept				= default;
			Metadata& operator=(const Metadata&)		= default;
			Metadata& operator=(Metadata&&) noexcept	= default;
			~Metadata() noexcept						= default;

			const std::string& GetEncoding() const noexcept;

		private:
			std::string m_encoding;
	};
}