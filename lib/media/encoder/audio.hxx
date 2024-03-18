#pragma once

#include "media/encoder.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC Base: public Encoder::Base {
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