#pragma once

#include "media/encoder.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC Base: public Encoder::Base {
		public:
			Base(const Type&);
			Base(Type&&);
			virtual ~Base() noexcept		= 0;
	};
}