#pragma once

#include "../metadata/subtitle.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC Subtitle: public Stream {
		public:
			Subtitle(std::shared_ptr<Codec>, const Metadata::Subtitle&);
			Subtitle(std::shared_ptr<Codec>&&, Metadata::Subtitle&&) noexcept;
			Subtitle(const Subtitle&)					= default;
			Subtitle(Subtitle&&) noexcept				= default;
			Subtitle& operator=(const Subtitle&)		= default;
			Subtitle& operator=(Subtitle&&) noexcept	= default;
			~Subtitle() noexcept						= default;

			const Metadata::Subtitle& GetMetadata() const noexcept;

		private:
			Metadata::Subtitle m_metadata;
	};
}