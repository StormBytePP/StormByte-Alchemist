#pragma once

#include "../codec.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC SubtitleCodec: public Codec {
		public:
			SubtitleCodec(std::string&&, std::string&&) noexcept;
			SubtitleCodec(const SubtitleCodec&)				= default;
			SubtitleCodec(SubtitleCodec&&) noexcept			= default;
			SubtitleCodec& operator=(const SubtitleCodec&)	= default;
			SubtitleCodec& operator=(SubtitleCodec&&)			= default;
			virtual ~SubtitleCodec() noexcept				= 0;

			static std::list<std::shared_ptr<Codec>> All();
	};
}