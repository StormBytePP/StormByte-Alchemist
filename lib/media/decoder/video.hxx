#pragma once

#include "../decoder.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC Base: public Decoder::Base {
		public:
			Base(const Type&);
			Base(Type&&);
			Base(const Base&)				= default;
			Base(Base&&)					= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&)			= default;
			virtual ~Base() noexcept		= 0;
	};
}