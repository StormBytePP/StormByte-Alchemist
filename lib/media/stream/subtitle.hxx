#pragma once

#include "../metadata/subtitle.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC Subtitle: public Stream {
		public:
			Subtitle(std::shared_ptr<Codec>, const Metadata::Subtitle&);
			Subtitle(std::shared_ptr<Codec>&&, Metadata::Subtitle&&);
			Subtitle(const Subtitle&)				= default;
			Subtitle(Subtitle&&)					= default;
			Subtitle& operator=(const Subtitle&)	= default;
			Subtitle& operator=(Subtitle&&)			= default;
			~Subtitle()								= default;

			const Metadata::Subtitle& GetMetadata() const;

		private:
			Metadata::Subtitle m_metadata;
	};
}