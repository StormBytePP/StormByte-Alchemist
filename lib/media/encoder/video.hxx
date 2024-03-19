#pragma once

#include "../encoder.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC Base: public Encoder::Base {
		public:
			Base(const Type&);
			Base(Type&&);
			virtual ~Base() noexcept		= 0;
	};
}