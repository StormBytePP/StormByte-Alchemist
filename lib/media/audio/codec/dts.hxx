#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Audio {
	class DLL_PUBLIC DTS: public Codec {
		public:
			DTS() noexcept;
			DTS(const DTS&)				= default;
			DTS(DTS&&)					= default;
			DTS& operator=(const DTS&)	= default;
			DTS& operator=(DTS&&)		= default;
			~DTS() noexcept				= default;
	};
}