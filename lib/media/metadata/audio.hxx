#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media::Metadata {
	class DLL_PUBLIC Audio {
		public:
			Audio(const unsigned short&, const unsigned short&);
			Audio(unsigned short&&, unsigned short&&) noexcept;
			Audio(const Audio&)					= default;
			Audio(Audio&&) noexcept				= default;
			Audio& operator=(const Audio&)		= default;
			Audio& operator=(Audio&&) noexcept	= default;
			~Audio() noexcept					= default;

			const unsigned short& GetChannels() const noexcept;
			const unsigned short& GetSampleRate() const noexcept;
			/**
			 * This function will return something like "Mono (44100Hz)", etc
			 */
			std::string GetFriendlyName() const;

		private:
			unsigned short m_channels, m_sample_rate;
	};
}