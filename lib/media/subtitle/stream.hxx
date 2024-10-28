#pragma once

#include "codec.hxx"
#include "metadata.hxx"
#include "../stream.hxx"

namespace Alchemist::Media::Subtitle {
	class DLL_PUBLIC Stream: public Media::Stream {
		public:
			Stream() noexcept						= default;
			Stream(const Stream&)					= default;
			Stream(Stream&&) noexcept				= default;
			Stream& operator=(const Stream&)		= default;
			Stream& operator=(Stream&&) noexcept	= default;
			~Stream() noexcept						= default;

			void SetMetadata(const Metadata&);
			void SetMetadata(Metadata&&) noexcept;
	};
}