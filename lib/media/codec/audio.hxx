#pragma once

#include "../codec.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC AudioCodec: public Codec {
		public:
			AudioCodec(std::string&&, std::string&&) noexcept;
			AudioCodec(const AudioCodec&)				= default;
			AudioCodec(AudioCodec&&) noexcept			= default;
			AudioCodec& operator=(const AudioCodec&)	= default;
			AudioCodec& operator=(AudioCodec&&)			= default;
			virtual ~AudioCodec() noexcept				= 0;

			static std::list<std::shared_ptr<Codec>> All();
	};
}