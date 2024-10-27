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
			Video(Atomic::Resolution&&, Atomic::Color&&, unsigned int&&, Atomic::HDR10&&);
			Video(const Video&)				= default;
			Video(Video&&)					= default;
			Video& operator=(const Video&)	= default;
			Video& operator=(Video&&)		= default;
			~Video()						= default;

			const Atomic::Resolution& 			GetResolution() const;
			const Atomic::Color& 				GetColor() const;
			const unsigned int&					GetFrames() const;
			const std::optional<Atomic::HDR10>&	GetHDR10() const;

		private:
			Atomic::Resolution m_resolution;
			Atomic::Color m_color;
			unsigned int m_frames;
			std::optional<Atomic::HDR10> m_hdr10;
	};
}