#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Audio {
	class DLL_PUBLIC FDK_AAC: public Codec {
		public:
			FDK_AAC() noexcept;
			FDK_AAC(const FDK_AAC&)				= default;
			FDK_AAC(FDK_AAC&&)					= default;
			FDK_AAC& operator=(const FDK_AAC&)	= default;
			FDK_AAC& operator=(FDK_AAC&&)		= default;
			~FDK_AAC() noexcept				= default;
	};
}