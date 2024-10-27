#pragma once

#include "../codec/subtitle.hxx"
#include "../metadata/subtitle.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC SubtitleStream: public Stream {
		public:
			SubtitleStream(std::unique_ptr<SubtitleCodec>&&, const Metadata::Subtitle&);
			SubtitleStream(std::unique_ptr<SubtitleCodec>&&, Metadata::Subtitle&&) noexcept;
			SubtitleStream(const SubtitleStream&)					= delete;
			SubtitleStream(SubtitleStream&&) noexcept				= default;
			SubtitleStream& operator=(const SubtitleStream&)		= delete;
			SubtitleStream& operator=(SubtitleStream&&) noexcept	= default;
			~SubtitleStream() noexcept								= default;

			const Metadata::Subtitle& GetMetadata() const noexcept;

		private:
			Metadata::Subtitle m_metadata;
	};
}