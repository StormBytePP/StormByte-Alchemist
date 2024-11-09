#pragma once

#include <Alchemy/media/video/color.hxx>
#include <Alchemy/media/video/hdr10.hxx>
#include <Alchemy/media/video/resolution.hxx>
#include <Alchemy/media/metadata.hxx>

namespace Alchemy::Media::Video {
	class ALCHEMY_PUBLIC Metadata: public Media::Metadata {
		public:
			Metadata() noexcept							= default;
			Metadata(const Metadata&)					= default;
			Metadata(Metadata&&) noexcept				= default;
			Metadata& operator=(const Metadata&)		= default;
			Metadata& operator=(Metadata&&) noexcept	= default;
			~Metadata() noexcept						= default;

			const std::optional<Resolution>& 	GetResolution() const noexcept;
			void								SetResolution(const Resolution&);
			void								SetResolution(Resolution&&) noexcept;
			const std::optional<Color>&			GetColor() const noexcept;
			void								SetColor(const Color&);
			void								SetColor(Color&&) noexcept;
			const std::optional<unsigned int>&	GetFrames() const noexcept;
			void								SetFrames(const unsigned int&);
			void								SetFrames(unsigned int&&) noexcept;
			const std::optional<HDR10>&			GetHDR10() const noexcept;
			void								SetHDR10(const HDR10&);
			void								SetHDR10(HDR10&&) noexcept;
			std::string							GetString() const override;

		private:
			std::optional<Resolution> m_resolution;
			std::optional<Color> m_color;
			std::optional<unsigned int> m_frames;
			std::optional<HDR10> m_hdr10;
	};
}