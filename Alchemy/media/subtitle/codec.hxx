#pragma once

#include <Alchemy/media/codec.hxx>

#include <map>

namespace Alchemist::Media::Subtitle {
	class ALCHEMY_PUBLIC Codec: public Media::Codec {
		public:
			Codec(std::string&&, std::string&&, std::string&&) noexcept;
			Codec(const Codec&)				= default;
			Codec(Codec&&) noexcept			= default;
			Codec& operator=(const Codec&)	= default;
			Codec& operator=(Codec&&)		= default;
			virtual ~Codec() noexcept		= 0;

			static const std::map<std::string, std::shared_ptr<Codec>> All;
	};
}