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

			virtual const std::list<Feature> get_features() const;
	};
}