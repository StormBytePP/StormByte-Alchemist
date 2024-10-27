#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media::Metadata {
	class DLL_PUBLIC Subtitle {
		public:
			Subtitle(const std::string&);
			Subtitle(std::string&&);
			Subtitle(const Subtitle&)				= default;
			Subtitle(Subtitle&&)					= default;
			Subtitle& operator=(const Subtitle&)	= default;
			Subtitle& operator=(Subtitle&&)			= default;
			~Subtitle()								= default;

			const std::string& GetEncoding() const;

		private:
			std::string m_encoding;
	};
}