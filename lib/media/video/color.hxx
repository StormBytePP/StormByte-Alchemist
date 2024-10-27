#pragma once

#include "visibility.h"

#include <list>
#include <string>

namespace Alchemist::Media::Video {
	class DLL_PUBLIC Color {
		public:
			static DLL_PUBLIC const Color DEFAULT;

			Color(const std::string&, const std::string&, const std::string&, const std::string&);
			Color(std::string&&, std::string&&, std::string&&, std::string&&) noexcept;
			Color(const Color&)					= default;
			Color(Color&&) noexcept				= default;
			Color& operator=(const Color&)		= default;
			Color& operator=(Color&&) noexcept	= default;
			~Color() noexcept					= default;

			const std::string& 		GetPrimaries() const noexcept;
			const std::string& 		GetMatrix() const noexcept;
			const std::string& 		GetTransfer() const noexcept;
			const std::string& 		GetPixelFormat() const noexcept;
			std::list<std::string>	GetParameters() const;

		private:
			std::string m_prim, m_matrix, m_transfer, m_pix_fmt;
	};
}