#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media::Metadata::Atomic {
	class DLL_PUBLIC Color {
		public:
			static DLL_PUBLIC const Color DEFAULT;
			
			Color(const std::string&, const std::string&, const std::string&, const std::string&);
			Color(std::string&&, std::string&&, std::string&&, std::string&&);
			Color(const Color&)				= default;
			Color(Color&&)					= default;
			Color& operator=(const Color&)	= default;
			Color& operator=(Color&&)		= default;
			~Color()						= default;

			const std::string& 	GetPrimaries() const;
			const std::string& 	GetMatrix() const;
			const std::string& 	GetTransfer() const;
			const std::string& 	GetPixelFormat() const;
			std::string			GetString() const;

		private:
			std::string m_prim, m_matrix, m_transfer, m_pix_fmt;
	};
}