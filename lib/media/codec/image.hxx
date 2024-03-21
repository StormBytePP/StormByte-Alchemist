#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Codec::Image {
	class DLL_PUBLIC Base: public Codec::Base {
		public:
			Base(const Codec::Type&);
			Base(Codec::Type&&);
			virtual ~Base() noexcept = 0;

			bool is_video() 	const noexcept override;
			bool is_audio() 	const noexcept override;
			bool is_image() 	const noexcept override;
			bool is_subtitle()	const noexcept override;
	};
}