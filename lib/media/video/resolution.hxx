#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media::Video {
	class ALCHEMY_PUBLIC Resolution {
		public:
			Resolution(const unsigned short&, const unsigned short&);
			Resolution(unsigned short&&, unsigned short&&) noexcept;
			Resolution(const Resolution&)					= default;
			Resolution(Resolution&&) noexcept				= default;
			Resolution& operator=(const Resolution&)		= default;
			Resolution& operator=(Resolution&&) noexcept	= default;
			~Resolution() noexcept							= default;

			const unsigned short& GetWidth() const noexcept;
			const unsigned short& GetHeight() const noexcept;
			std::string GetName() const;
			/**
			 * This function will return resolution name like "720p", "FullHD", "UHD", etc
			 */
			std::string GetFriendlyName() const;

		private:
			unsigned short m_width, m_height;
	};
}