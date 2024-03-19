#pragma once

#include "../decoder.hxx"

namespace Alchemist::Media::Decoder::Image {
	class DLL_PUBLIC Base: public Decoder::Base {
		public:
			Base(const Type&);
			Base(Type&&);
			virtual ~Base() noexcept		= 0;
	};
}