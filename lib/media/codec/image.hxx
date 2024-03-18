#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC Base: public Codec::Base {
		public:
			Base(const Codec::Type&);
			Base(Codec::Type&&);
			Base(const Base&)				= default;
			Base(Base&&) noexcept			= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&) noexcept= default;
			virtual ~Base() noexcept		= default;

			bool is_video() const noexcept;
			bool is_audio() const noexcept;
			bool is_image() const noexcept;
	};
}