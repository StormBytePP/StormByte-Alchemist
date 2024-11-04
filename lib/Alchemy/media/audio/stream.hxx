#pragma once

#include <Alchemy/media/audio/codec.hxx>
#include <Alchemy/media/audio/metadata.hxx>
#include <Alchemy/media/stream.hxx>

namespace Alchemist::Media::Audio {
	class ALCHEMY_PUBLIC Stream: public Media::Stream {
		public:
			Stream(const unsigned short&) noexcept;
			Stream(const Stream&)					= default;
			Stream(Stream&&) noexcept				= default;
			Stream& operator=(const Stream&)		= default;
			Stream& operator=(Stream&&) noexcept	= default;
			~Stream() noexcept						= default;

			void SetMetadata(const Metadata&);
			void SetMetadata(Metadata&&) noexcept;
	};
}