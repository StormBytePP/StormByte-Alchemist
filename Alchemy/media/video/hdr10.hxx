#pragma once

#include <Alchemy/visibility.h>

#include <list>
#include <optional>
#include <string>
#include <utility>

namespace Alchemy::Media::Video {
	class ALCHEMY_PUBLIC HDR10 {
		public:
			static const HDR10 DEFAULT;

			HDR10(const std::pair<int, int>&,
				const std::pair<int, int>&,
				const std::pair<int, int>&,
				const std::pair<int, int>&,
				const std::pair<int, unsigned int>&
			);
			HDR10(const std::pair<int, int>&,
				const std::pair<int, int>&,
				const std::pair<int, int>&,
				const std::pair<int, int>&,
				const std::pair<int, unsigned int>&,
				const std::pair<int, int>&
			);
			HDR10(std::pair<int, int>&&,
				std::pair<int, int>&&,
				std::pair<int, int>&&,
				std::pair<int, int>&&,
				std::pair<int, unsigned int>&&
			);
			HDR10(std::pair<int, int>&&,
				std::pair<int, int>&&,
				std::pair<int, int>&&,
				std::pair<int, int>&&,
				std::pair<int, unsigned int>&&,
				std::pair<int, int>&&
			);
			HDR10(const HDR10&)					= default;
			HDR10(HDR10&&) noexcept				= default;
			HDR10& operator=(const HDR10&)		= default;
			HDR10& operator=(HDR10&&) noexcept	= default;
			~HDR10() noexcept					= default;

			const std::pair<int, int>& 				GetRedPoint() const noexcept;
			const std::pair<int, int>& 				GetGreenPoint() const noexcept;
			const std::pair<int, int>& 				GetBluePoint() const noexcept;
			const std::pair<int, int>& 				GetWhitePoint() const noexcept;
			const std::pair<int, unsigned int>& 					GetLuminance() const noexcept;
			const std::optional<std::pair<int, int>>& GetLightLevel() const noexcept;
			void															SetLightLevel(const std::pair<int, int>&);
			void															SetLightLevel(std::pair<int, int>&&) noexcept;
			const std::optional<std::string>&								GetPlusFile() const noexcept;
			void															SetPlusFile(const std::string&);
			void															SetPlusFile(std::string&&) noexcept;
			std::list<std::string>											GetParameters() const;

		private:
			std::pair<int, int> m_red, m_green, m_blue, m_white;
			std::pair<int, unsigned int> m_luminance;
			std::optional<std::pair<int, int>> m_light_level;
			std::optional<std::string> m_hdr10plus;
	};
}