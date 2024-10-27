#pragma once

#include "../codec.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC VideoCodec: public Codec {
		public:
			VideoCodec(std::string&&, std::string&&) noexcept;
			VideoCodec(const VideoCodec&)				= default;
			VideoCodec(VideoCodec&&) noexcept			= default;
			VideoCodec& operator=(const VideoCodec&)	= default;
			VideoCodec& operator=(VideoCodec&&)			= default;
			virtual ~VideoCodec() noexcept				= 0;

			static std::list<std::shared_ptr<Codec>> All();
	};
}