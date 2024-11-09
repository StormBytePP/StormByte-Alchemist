#pragma once

#include <Alchemy/media/video/codec.hxx>
#include <Alchemy/media/video/metadata.hxx>
#include <Alchemy/media/stream.hxx>

namespace Alchemy::Media::Video {
	class ALCHEMY_PUBLIC Stream: public Media::Stream {
		public:
			Stream(const int&) noexcept;
			Stream(const Stream&)					= default;
			Stream(Stream&&) noexcept				= default;
			Stream& operator=(const Stream&)		= default;
			Stream& operator=(Stream&&) noexcept	= default;
			~Stream() noexcept						= default;

			void SetMetadata(const Metadata&);
			void SetMetadata(Metadata&&) noexcept;
	};
}