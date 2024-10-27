#pragma once

#include "../codec/audio.hxx"
#include "../metadata/audio.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC AudioStream: public Stream {
		public:
			AudioStream(std::shared_ptr<AudioCodec>, const Metadata::Audio&);
			AudioStream(std::shared_ptr<AudioCodec>, Metadata::Audio&&) noexcept;
			AudioStream(const AudioStream&)					= default;
			AudioStream(AudioStream&&) noexcept				= default;
			AudioStream& operator=(const AudioStream&)		= default;
			AudioStream& operator=(AudioStream&&) noexcept	= default;
			~AudioStream() noexcept							= default;

			const Metadata::Audio& GetMetadata() const noexcept;

		private:
			Metadata::Audio m_metadata;
	};
}