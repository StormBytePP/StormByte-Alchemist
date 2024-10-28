#pragma once

#include "visibility.h"

#include <list>
#include <string>

namespace Alchemist::Media::Video {
	class DLL_PUBLIC Color {
		public:
			static DLL_PUBLIC const Color DEFAULT;

			Color()								= default;
			Color(const std::string&, const std::string&, const std::string&, const std::string&);
			Color(std::string&&, std::string&&, std::string&&, std::string&&) noexcept;
			Color(std::string&&) noexcept;
			Color(const Color&)					= default;
			Color(Color&&) noexcept				= default;
			Color& operator=(const Color&)		= default;
			Color& operator=(Color&&) noexcept	= default;
			~Color() noexcept					= default;

			const std::optional<std::string>&	GetPrimaries() const noexcept;
			void								SetPrimaries(const std::string&);
			void								SetPrimaries(std::string&&) noexcept;
			const std::optional<std::string>& 	GetMatrix() const noexcept;
			void								SetMatrix(const std::string&);
			void								SetMatrix(std::string&&) noexcept;
			const std::optional<std::string>& 	GetTransfer() const noexcept;
			void								SetTransfer(const std::string&);
			void								SetTransfer(std::string&&) noexcept;
			const std::optional<std::string>&	GetPixelFormat() const noexcept;
			void								SetPixelFormat(const std::string&);
			void								SetPixelFormat(std::string&&) noexcept;
			std::list<std::string>				GetParameters() const;
			bool								IsHDR10() const noexcept;

		private:
			std::optional<std::string> m_prim, m_matrix, m_transfer, m_pix_fmt;
	};
}