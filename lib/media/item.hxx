#pragma once

#include "attribute.hxx"

#include <list>

namespace Alchemist::Media {
	class DLL_PUBLIC Item {
		public:
			Item()							= default;
			Item(const Item&)				= default;
			Item(Item&&) noexcept			= default;
			Item& operator=(const Item&)	= default;
			Item& operator=(Item&&) noexcept= default;
			virtual ~Item() noexcept		= 0;

			unsigned short get_attributes() const noexcept;
			bool has_attribute(const Attribute&) const noexcept;

		protected:
			unsigned int m_attrs: 5;
	};
}