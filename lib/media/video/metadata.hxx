#pragma once

#include "color.hxx"
#include "hdr10.hxx"
#include "resolution.hxx"
#include "../metadata.hxx"

namespace Alchemist::Media::Video {
	class DLL_PUBLIC Metadata: public Media::Metadata {
		public:
			Metadata(const Resolution&, const Color&, const unsigned int&);
			Metadata(const Resolution&, const Color&, const unsigned int&, const HDR10&);
			Metadata(Resolution&&, Color&&, unsigned int&&);
			Metadata(Resolution&&, Color&&, unsigned int&&, HDR10&&) noexcept;
			Metadata(const Metadata&)					= default;
			Metadata(Metadata&&) noexcept				= default;
			Metadata& operator=(const Metadata&)		= default;
			Metadata& operator=(Metadata&&) noexcept	= default;
			~Metadata() noexcept						= default;

			const Resolution& 			GetResolution() const noexcept;
			const Color& 				GetColor() const noexcept;
			const unsigned int&			GetFrames() const noexcept;
			const std::optional<HDR10>&	GetHDR10() const noexcept;
			std::string					GetString() const override;

		private:
			Resolution m_resolution;
			Color m_color;
			unsigned int m_frames;
			std::optional<HDR10> m_hdr10;
	};
}