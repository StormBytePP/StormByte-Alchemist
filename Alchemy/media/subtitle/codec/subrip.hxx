#pragma once

#include <Alchemy/media/subtitle/codec.hxx>

namespace Alchemy::Media::Subtitle {
	class ALCHEMY_PUBLIC Subrip: public Codec {
		public:
			Subrip() noexcept;
			Subrip(const Subrip&)				= default;
			Subrip(Subrip&&)					= default;
			Subrip& operator=(const Subrip&)	= default;
			Subrip& operator=(Subrip&&)			= default;
			~Subrip() noexcept					= default;
	};
}