#pragma once

#include "../audio.hxx"

namespace Alchemist::Media::Encoder::Audio {
	class DLL_PUBLIC VORBIS_LIBVORBIS final: public Base {
		public:
			VORBIS_LIBVORBIS();
			VORBIS_LIBVORBIS(const VORBIS_LIBVORBIS&)				= default;
			VORBIS_LIBVORBIS(VORBIS_LIBVORBIS&&) noexcept			= default;
			VORBIS_LIBVORBIS& operator=(const VORBIS_LIBVORBIS&)	= default;
			VORBIS_LIBVORBIS& operator=(VORBIS_LIBVORBIS&&) noexcept= default;
			~VORBIS_LIBVORBIS() noexcept							= default;
	};
}