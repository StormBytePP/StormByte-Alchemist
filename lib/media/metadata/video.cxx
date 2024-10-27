#include "video.hxx"

using namespace Alchemist::Media::Metadata;

Video::Video(const Atomic::Resolution& res, const Atomic::Color& color, const unsigned int& frames):
m_resolution(res), m_color(color), m_frames(frames) {}

Video::Video(const Atomic::Resolution& res, const Atomic::Color& color, const unsigned int& frames, const Atomic::HDR10& hdr10):
m_resolution(res), m_color(color), m_frames(frames), m_hdr10(hdr10) {}

Video::Video(Atomic::Resolution&& res, Atomic::Color&& color, unsigned int&& frames):
m_resolution(std::move(res)), m_color(std::move(color)), m_frames(std::move(frames)) {}

Video::Video(Atomic::Resolution&& res, Atomic::Color&& color, unsigned int&& frames, Atomic::HDR10&& hdr10):
m_resolution(std::move(res)), m_color(std::move(color)), m_frames(std::move(frames)), m_hdr10(std::move(hdr10)) {}

const Atomic::Resolution& Video::GetResolution() const { return m_resolution; }

const Atomic::Color& Video::GetColor() const { return m_color; }

const unsigned int& Video::GetFrames() const { return m_frames; }

const std::optional<Atomic::HDR10>&	Video::GetHDR10() const { return m_hdr10; }