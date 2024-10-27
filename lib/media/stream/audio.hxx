#pragma once

#include "../metadata/audio.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC Audio: public Stream {
		public:
			Audio(std::unique_ptr<Codec>&&, const Metadata::Audio&);
			Audio(std::unique_ptr<Codec>&&, Metadata::Audio&&) noexcept;
			Audio(const Audio&)					= delete;
			Audio(Audio&&) noexcept				= default;
			Audio& operator=(const Audio&)		= delete;
			Audio& operator=(Audio&&) noexcept	= default;
			~Audio() noexcept					= default;

			const Metadata::Audio& GetMetadata() const noexcept;

		private:
			Metadata::Audio m_metadata;
	};
}