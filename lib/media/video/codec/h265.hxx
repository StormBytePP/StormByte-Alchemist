#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Video {
	class ALCHEMY_PUBLIC H265: public Codec {
		public:
			H265() noexcept;
			H265(const H265&)				= default;
			H265(H265&&)					= default;
			H265& operator=(const H265&)	= default;
			H265& operator=(H265&&)			= default;
			~H265() noexcept				= default;
	};
}