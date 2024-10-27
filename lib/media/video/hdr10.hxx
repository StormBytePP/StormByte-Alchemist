#pragma once

#include "visibility.h"

#include <list>
#include <optional>
#include <string>
#include <utility>

namespace Alchemist::Media::Video {
	class DLL_PUBLIC HDR10 {
		public:
			static DLL_PUBLIC const HDR10 DEFAULT;

			HDR10(const std::pair<unsigned short, unsigned short>&,
				const std::pair<unsigned short, unsigned short>&,
				const std::pair<unsigned short, unsigned short>&,
				const std::pair<unsigned short, unsigned short>&,
				const std::pair<unsigned short, unsigned int>&,
				const std::optional<std::string>& hdr10plus = std::make_optional<std::string>());
			HDR10(const std::pair<unsigned short, unsigned short>&,
				const std::pair<unsigned short, unsigned short>&,
				const std::pair<unsigned short, unsigned short>&,
				const std::pair<unsigned short, unsigned short>&,
				const std::pair<unsigned short, unsigned int>&,
				const std::pair<unsigned short, unsigned short>&,
				const std::optional<std::string>& = std::make_optional<std::string>());
			HDR10(std::pair<unsigned short, unsigned short>&&,
				std::pair<unsigned short, unsigned short>&&,
				std::pair<unsigned short, unsigned short>&&,
				std::pair<unsigned short, unsigned short>&&,
				std::pair<unsigned short, unsigned int>&&,
				std::optional<std::string>&& hdr10plus = std::make_optional<std::string>());
			HDR10(std::pair<unsigned short, unsigned short>&&,
				std::pair<unsigned short, unsigned short>&&,
				std::pair<unsigned short, unsigned short>&&,
				std::pair<unsigned short, unsigned short>&&,
				std::pair<unsigned short, unsigned int>&&,
				std::pair<unsigned short, unsigned short>&&,
				std::optional<std::string>&& hdr10plus = std::make_optional<std::string>());
			HDR10(const HDR10&)					= default;
			HDR10(HDR10&&) noexcept				= default;
			HDR10& operator=(const HDR10&)		= default;
			HDR10& operator=(HDR10&&) noexcept	= default;
			~HDR10() noexcept					= default;

			const std::pair<unsigned short, unsigned short>& 				GetRedPoint() const noexcept;
			const std::pair<unsigned short, unsigned short>& 				GetGreenPoint() const noexcept;
			const std::pair<unsigned short, unsigned short>& 				GetBluePoint() const noexcept;
			const std::pair<unsigned short, unsigned short>& 				GetWhitePoint() const noexcept;
			const std::pair<unsigned short, unsigned int>& 					GetLuminance() const noexcept;
			const std::optional<std::pair<unsigned short, unsigned short>>& GetLightLevel() const noexcept;
			const std::optional<std::string>&								GetPlusFile() const noexcept;
			std::list<std::string>											GetParameters() const;

		private:
			std::pair<unsigned short, unsigned short> m_red, m_green, m_blue, m_white;
			std::pair<unsigned short, unsigned int> m_luminance;
			std::optional<std::pair<unsigned short, unsigned short>> m_light_level;
			std::optional<std::string> m_hdr10plus;
	};
}