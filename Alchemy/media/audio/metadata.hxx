#pragma once

#include <Alchemy/media/metadata.hxx>

#include <string>

namespace Alchemist::Media::Audio {
	class ALCHEMY_PUBLIC Metadata: public Media::Metadata {
		public:
			Metadata(const int&, const int&);
			Metadata(int&&, int&&) noexcept;
			Metadata(const Metadata&)					= default;
			Metadata(Metadata&&) noexcept				= default;
			Metadata& operator=(const Metadata&)		= default;
			Metadata& operator=(Metadata&&) noexcept	= default;
			~Metadata() noexcept						= default;

			const int& 	GetChannels() const noexcept;
			const int& 	GetSampleRate() const noexcept;
			std::string 			GetString() const override;

		private:
			int m_channels, m_sample_rate;
	};
}