#include "metadata.hxx"

using namespace Alchemist::Media::Video;

Metadata::Metadata(const Resolution& res, const Color& color, const unsigned int& frames):
m_resolution(res), m_color(color), m_frames(frames) {}

Metadata::Metadata(const Resolution& res, const Color& color, const unsigned int& frames, const HDR10& hdr10):
m_resolution(res), m_color(color), m_frames(frames), m_hdr10(hdr10) {}

Metadata::Metadata(Resolution&& res, Color&& color, unsigned int&& frames):
m_resolution(std::move(res)), m_color(std::move(color)), m_frames(std::move(frames)) {}

Metadata::Metadata(Resolution&& res, Color&& color, unsigned int&& frames, HDR10&& hdr10) noexcept:
m_resolution(std::move(res)), m_color(std::move(color)), m_frames(std::move(frames)), m_hdr10(std::move(hdr10)) {}

const Resolution& Metadata::GetResolution() const noexcept { return m_resolution; }

const Color& Metadata::GetColor() const noexcept { return m_color; }

const unsigned int& Metadata::GetFrames() const noexcept { return m_frames; }

const std::optional<HDR10>&	Metadata::GetHDR10() const noexcept { return m_hdr10; }