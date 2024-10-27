#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media::Metadata {
	class DLL_PUBLIC Audio {
		public:
			Audio(const unsigned short&, const unsigned short&);
			Audio(const Audio&)				= default;
			Audio(Audio&&)					= default;
			Audio& operator=(const Audio&)	= default;
			Audio& operator=(Audio&&)		= default;

			const unsigned short& GetChannels() const;
			const unsigned short& GetSampleRate() const;
			/**
			 * This function will return something like "Mono (44100Hz)", etc
			 */
			std::string GetFriendlyName() const;

		private:
			unsigned short m_channels, m_sample_rate;
	};
}