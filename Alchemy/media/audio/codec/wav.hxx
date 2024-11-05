#pragma once

#include <Alchemy/media/audio/codec.hxx>

namespace Alchemist::Media::Audio {
	class ALCHEMY_PUBLIC WAV: public Codec {
		public:
			WAV() noexcept;
			WAV(const WAV&)				= default;
			WAV(WAV&&)					= default;
			WAV& operator=(const WAV&)	= default;
			WAV& operator=(WAV&&)		= default;
			~WAV() noexcept				= default;
	};
}