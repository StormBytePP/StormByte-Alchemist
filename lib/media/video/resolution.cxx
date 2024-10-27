#include "resolution.hxx"

using namespace Alchemist::Media::Video;

Resolution::Resolution(const unsigned short& width, const unsigned short& height):
m_width(width), m_height(height) {}

Resolution::Resolution(unsigned short&& width, unsigned short&& height) noexcept:
m_width(std::move(width)), m_height(std::move(height)) {}

const unsigned short& Resolution::GetWidth() const noexcept { return m_width; }

const unsigned short& Resolution::GetHeight() const noexcept { return m_height; }

std::string Resolution::GetName() const {
	return std::to_string(m_width) + "x" + std::to_string(m_height);
}

std::string Resolution::GetFriendlyName() const {
	if (m_height <= 480)
		return "SD";
	else if (m_height <= 720)
		return "HD";
	else if (m_height <= 1080)
		return "FullHD";
	else if (m_height <= 1080)
		return "QHD";
	else if (m_height <= 2160)
		return "UHD";
	else if (m_height <= 2988)
		return "16MP";
	else
		return "FullUHD";
}