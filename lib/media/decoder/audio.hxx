#pragma once

#include "media/decoder.hxx"

namespace Alchemist::Media::Decoder::Audio {
	class DLL_PUBLIC Base: public Decoder::Base {
		public:
			Base(const Type&);
			Base(Type&&);
			virtual ~Base() noexcept		= 0;
	};
}