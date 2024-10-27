#pragma once

#include "codec.hxx"
#include "metadata.hxx"
#include "../stream.hxx"

namespace Alchemist::Media::Subtitle {
	class DLL_PUBLIC Stream: public Media::Stream {
		public:
			Stream(std::shared_ptr<Codec>, const Metadata&);
			Stream(std::shared_ptr<Codec>, Metadata&&) noexcept;
			Stream(const Stream&)					= delete;
			Stream(Stream&&) noexcept				= default;
			Stream& operator=(const Stream&)		= delete;
			Stream& operator=(Stream&&) noexcept	= default;
			~Stream() noexcept						= default;

			const Metadata& GetMetadata() const noexcept;

		private:
			Metadata m_metadata;
	};
}