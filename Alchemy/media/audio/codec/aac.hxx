#pragma once

#include <Alchemy/media/audio/codec.hxx>

namespace Alchemist::Media::Audio {
	class ALCHEMY_PUBLIC AAC: public Codec {
		public:
			AAC() noexcept;
			AAC(const AAC&)				= default;
			AAC(AAC&&)					= default;
			AAC& operator=(const AAC&)	= default;
			AAC& operator=(AAC&&)		= default;
			~AAC() noexcept				= default;
	};
}