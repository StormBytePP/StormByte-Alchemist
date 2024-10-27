#pragma once

#include "../codec/video.hxx"
#include "../metadata/video.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC VideoStream: public Stream {
		public:
			VideoStream(std::unique_ptr<VideoCodec>&&, const Metadata::Video&);
			VideoStream(std::unique_ptr<VideoCodec>&&, Metadata::Video&&) noexcept;
			VideoStream(const VideoStream&)					= delete;
			VideoStream(VideoStream&&) noexcept				= default;
			VideoStream& operator=(const VideoStream&)		= delete;
			VideoStream& operator=(VideoStream&&) noexcept	= default;
			~VideoStream() noexcept							= default;

			const Metadata::Video& GetMetadata() const noexcept;

		private:
			Metadata::Video m_metadata;
	};
}