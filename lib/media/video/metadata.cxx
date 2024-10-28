#include "metadata.hxx"

using namespace Alchemist::Media::Video;

const std::optional<Resolution>& Metadata::GetResolution() const noexcept { return m_resolution; }

void Metadata::SetResolution(const Resolution& res) { m_resolution = res; }

void Metadata::SetResolution(Resolution&& res) noexcept { m_resolution = std::move(res); }

const std::optional<Color>& Metadata::GetColor() const noexcept { return m_color; }

void Metadata::SetColor(const Color& color) { m_color = color; }

void Metadata::SetColor(Color&& color) noexcept { m_color = std::move(color); }

const std::optional<unsigned int>& Metadata::GetFrames() const noexcept { return m_frames; }

void Metadata::SetFrames(const unsigned int& frames) { m_frames = frames; }

void Metadata::SetFrames(unsigned int&& frames) noexcept { m_frames = std::move(frames); }

const std::optional<HDR10>& Metadata::GetHDR10() const noexcept { return m_hdr10; }

void Metadata::SetHDR10(const HDR10& hdr10) { m_hdr10 = hdr10; }

void Metadata::SetHDR10(HDR10&& hdr10) noexcept { m_hdr10 = std::move(hdr10); }

std::string Metadata::GetString() const {
	std::string str = m_resolution ? m_resolution->GetFriendlyName() : "";

	if (m_hdr10) {
		str += "(HDR10";
		if (m_hdr10->GetPlusFile()) str += "+";
		str += ")";
	}

	return str;
}