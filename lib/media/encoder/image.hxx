#pragma once

#include "../encoder.hxx"

namespace Alchemist::Media::Encoder::Image {
	class DLL_PUBLIC Base: public Encoder::Base {
		public:
			Base(const Type&);
			Base(Type&&);
			virtual ~Base() noexcept		= 0;
	};
}