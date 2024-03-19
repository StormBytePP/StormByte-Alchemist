#pragma once

#include "attribute.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC Item {
		public:
			virtual ~Item() noexcept		= 0;

			unsigned short get_attributes() const noexcept;
			bool has_attribute(const Attribute&) const noexcept;

		protected:
			unsigned int m_attrs: 5;
	};
}