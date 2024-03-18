#pragma once

#include "media/decoder.hxx"

namespace Alchemist::Media::Decoder::Audio {
	class DLL_PUBLIC Base: public Decoder::Base {
		public:
			Base(const Type&);
			Base(Type&&);
			Base(const Base&)				= default;
			Base(Base&&) noexcept			= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&) noexcept= default;
			virtual ~Base() noexcept		= 0;
	};
}