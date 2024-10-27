#pragma once

#include "../metadata/video.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC Video: public Stream {
		public:
			Video(std::shared_ptr<Codec>, const Metadata::Video&);
			Video(std::shared_ptr<Codec>&&, Metadata::Video&&) noexcept;
			Video(const Video&)					= default;
			Video(Video&&) noexcept				= default;
			Video& operator=(const Video&)		= default;
			Video& operator=(Video&&) noexcept	= default;
			~Video() noexcept					= default;

			const Metadata::Video& GetMetadata() const noexcept;

		private:
			Metadata::Video m_metadata;
	};
}