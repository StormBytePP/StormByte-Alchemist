#pragma once

#include "atomic/color.hxx"
#include "atomic/hdr10.hxx"
#include "atomic/resolution.hxx"

namespace Alchemist::Media::Metadata {
	class DLL_PUBLIC Video {
		public:
			Video(const Atomic::Resolution&, const Atomic::Color&, const unsigned int&);
			Video(const Atomic::Resolution&, const Atomic::Color&, const unsigned int&, const Atomic::HDR10&);
			Video(Atomic::Resolution&&, Atomic::Color&&, unsigned int&&);
			Video(Atomic::Resolution&&, Atomic::Color&&, unsigned int&&, Atomic::HDR10&&) noexcept;
			Video(const Video&)					= default;
			Video(Video&&) noexcept				= default;
			Video& operator=(const Video&)		= default;
			Video& operator=(Video&&) noexcept	= default;
			~Video() noexcept					= default;

			const Atomic::Resolution& 			GetResolution() const noexcept;
			const Atomic::Color& 				GetColor() const noexcept;
			const unsigned int&					GetFrames() const noexcept;
			const std::optional<Atomic::HDR10>&	GetHDR10() const noexcept;

		private:
			Atomic::Resolution m_resolution;
			Atomic::Color m_color;
			unsigned int m_frames;
			std::optional<Atomic::HDR10> m_hdr10;
	};
}