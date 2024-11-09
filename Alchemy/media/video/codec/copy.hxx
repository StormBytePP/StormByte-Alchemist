#pragma once

#include <Alchemy/media/video/codec.hxx>

namespace Alchemy::Media::Video {
	class ALCHEMY_PUBLIC Copy: public Codec {
		public:
			Copy() noexcept;
			Copy(const Copy&)				= default;
			Copy(Copy&&)					= default;
			Copy& operator=(const Copy&)	= default;
			Copy& operator=(Copy&&)			= default;
			~Copy() noexcept				= default;
	};
}