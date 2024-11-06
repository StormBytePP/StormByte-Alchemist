#pragma once

#include <Alchemy/visibility.h>

#include <string>

namespace Alchemist::Media::Video {
	class ALCHEMY_PUBLIC Resolution {
		public:
			Resolution(const int&, const int&);
			Resolution(int&&, int&&) noexcept;
			Resolution(const Resolution&)					= default;
			Resolution(Resolution&&) noexcept				= default;
			Resolution& operator=(const Resolution&)		= default;
			Resolution& operator=(Resolution&&) noexcept	= default;
			~Resolution() noexcept							= default;

			const int& GetWidth() const noexcept;
			const int& GetHeight() const noexcept;
			std::string GetName() const;
			/**
			 * This function will return resolution name like "720p", "FullHD", "UHD", etc
			 */
			std::string GetFriendlyName() const;

		private:
			int m_width, m_height;
	};
}