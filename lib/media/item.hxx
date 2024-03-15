#pragma once

#include "base.hxx"

#include <list>

namespace Alchemist::Media {
	class DLL_PUBLIC Item {
		public:
			Item()							= default;
			Item(const Item&)				= default;
			Item(Item&&)					= default;
			Item& operator=(const Item&)	= default;
			Item& operator=(Item&&)			= default;
			virtual ~Item()					= 0;

			unsigned short get_attributes() const;
			bool has_attribute(const Attribute&) const;

		protected:
			unsigned int m_attrs: 5;
	};
}