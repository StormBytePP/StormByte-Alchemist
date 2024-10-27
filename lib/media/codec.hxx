#pragma once

#include "visibility.h"

#include <list>
#include <string>

namespace Alchemist::Media {
	class DLL_PUBLIC Codec {
		public:
			Codec(std::string&&, std::string&&, std::string&&) noexcept;
			Codec(const Codec&)								= default;
			Codec(Codec&&) noexcept							= default;
			Codec& operator=(const Codec&)					= default;
			Codec& operator=(Codec&&) noexcept				= default;
			virtual ~Codec() noexcept						= 0;

			const std::string& GetName() const noexcept;
			const std::string& GetFFmpegName() const noexcept;
			const std::string& GetDescription() const noexcept;

		private:
			std::string m_name, m_ffmpeg_name, m_description;
	};
}