#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media::Metadata::Atomic {
	class DLL_PUBLIC Resolution {
		public:
			Resolution(const unsigned short&, const unsigned short&);
			Resolution(const Resolution&)				= default;
			Resolution(Resolution&&)					= default;
			Resolution& operator=(const Resolution&)	= default;
			Resolution& operator=(Resolution&&)			= default;
			~Resolution()								= default;

			const unsigned short& GetWidth() const;
			const unsigned short& GetHeight() const;
			std::string GetName() const;
			/**
			 * This function will return resolution name like "720p", "FullHD", "UHD", etc
			 */
			std::string GetFriendlyName() const;

		private:
			unsigned short m_width, m_height;
	};
}