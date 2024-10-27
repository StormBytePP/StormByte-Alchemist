#pragma once

#include "../metadata/subtitle.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC Subtitle: public Stream {
		public:
			Subtitle(std::unique_ptr<Codec>&&, const Metadata::Subtitle&);
			Subtitle(std::unique_ptr<Codec>&&, Metadata::Subtitle&&) noexcept;
			Subtitle(const Subtitle&)					= delete;
			Subtitle(Subtitle&&) noexcept				= default;
			Subtitle& operator=(const Subtitle&)		= delete;
			Subtitle& operator=(Subtitle&&) noexcept	= default;
			~Subtitle() noexcept						= default;

			const Metadata::Subtitle& GetMetadata() const noexcept;

		private:
			Metadata::Subtitle m_metadata;
	};
}