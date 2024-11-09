#pragma once

#include <Alchemy/media/audio/codec.hxx>

namespace Alchemy::Media::Audio {
	class ALCHEMY_PUBLIC DTS: public Codec {
		public:
			DTS() noexcept;
			DTS(const DTS&)				= default;
			DTS(DTS&&)					= default;
			DTS& operator=(const DTS&)	= default;
			DTS& operator=(DTS&&)		= default;
			~DTS() noexcept				= default;
	};
}