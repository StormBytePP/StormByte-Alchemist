#pragma once

#include "visibility.h"

#include <optional>
#include <string>
#include <utility>

namespace Alchemist::Media::Metadata::Atomic {
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
			HDR10(const HDR10&)				= default;
			HDR10(HDR10&&)					= default;
			HDR10& operator=(const HDR10&)	= default;
			HDR10& operator=(HDR10&&)		= default;
			~HDR10()						= default;

			const std::pair<unsigned short, unsigned short>& 				GetRedPoint() const;
			const std::pair<unsigned short, unsigned short>& 				GetGreenPoint() const;
			const std::pair<unsigned short, unsigned short>& 				GetBluePoint() const;
			const std::pair<unsigned short, unsigned short>& 				GetWhitePoint() const;
			const std::pair<unsigned short, unsigned int>& 					GetLuminance() const;
			const std::optional<std::pair<unsigned short, unsigned short>>& GetLightLevel() const;
			const std::optional<std::string>&								GetPlusFile() const;
			std::string														GetString() const;

		private:
			std::pair<unsigned short, unsigned short> m_red, m_green, m_blue, m_white;
			std::pair<unsigned short, unsigned int> m_luminance;
			std::optional<std::pair<unsigned short, unsigned short>> m_light_level;
			std::optional<std::string> m_hdr10plus;
	};
}