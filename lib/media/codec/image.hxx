#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC Base: public Codec::Base {
		public:
			Base(const Codec::Type&);
			Base(Codec::Type&&);

			bool is_video() const noexcept;
			bool is_audio() const noexcept;
			bool is_image() const noexcept;
	};
}