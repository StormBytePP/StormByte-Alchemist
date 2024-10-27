#pragma once

#include "codec.hxx"
#include "metadata.hxx"
#include "../stream.hxx"

namespace Alchemist::Media::Audio {
	class DLL_PUBLIC Stream: public Media::Stream {
		public:
			Stream(std::shared_ptr<Codec>, const Metadata&);
			Stream(std::shared_ptr<Codec>, Metadata&&) noexcept;
			Stream(std::shared_ptr<Codec>, std::shared_ptr<Metadata>) noexcept;
			Stream(const Stream&)					= default;
			Stream(Stream&&) noexcept				= default;
			Stream& operator=(const Stream&)		= default;
			Stream& operator=(Stream&&) noexcept	= default;
			~Stream() noexcept						= default;
	};
}