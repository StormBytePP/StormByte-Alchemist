#pragma once

#include <Alchemy/media/subtitle/codec.hxx>

namespace Alchemy::Media::Subtitle {
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