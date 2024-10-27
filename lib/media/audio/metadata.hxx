#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media::Audio {
	class DLL_PUBLIC Metadata {
		public:
			Metadata(const unsigned short&, const unsigned short&);
			Metadata(unsigned short&&, unsigned short&&) noexcept;
			Metadata(const Metadata&)					= default;
			Metadata(Metadata&&) noexcept				= default;
			Metadata& operator=(const Metadata&)		= default;
			Metadata& operator=(Metadata&&) noexcept	= default;
			~Metadata() noexcept						= default;

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