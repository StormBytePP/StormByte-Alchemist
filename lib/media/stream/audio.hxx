#pragma once

#include "../metadata/audio.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC Audio: public Stream {
		public:
			Audio(std::shared_ptr<Codec>, const Metadata::Audio&);
			Audio(std::shared_ptr<Codec>&&, Metadata::Audio&&);
			Audio(const Audio&)				= default;
			Audio(Audio&&)					= default;
			Audio& operator=(const Audio&)	= default;
			Audio& operator=(Audio&&)		= default;
			~Audio()						= default;

			const Metadata::Audio& GetMetadata() const;

		private:
			Metadata::Audio m_metadata;
	};
}