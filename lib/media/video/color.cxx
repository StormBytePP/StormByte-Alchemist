#include "color.hxx"

using namespace Alchemist::Media::Video;

const Color Color::DEFAULT = { "bt2020", "bt2020nc", "smpte2084", "yuv420p10le" };

Color::Color(const std::string& primaries, const std::string& matrix, const std::string& transfer, const std::string& pix_fmt):
m_prim(primaries), m_matrix(matrix), m_transfer(transfer), m_pix_fmt(pix_fmt) {}

Color::Color(std::string&& primaries, std::string&& matrix, std::string&& transfer, std::string&& pix_fmt) noexcept:
m_prim(std::move(primaries)), m_matrix(std::move(matrix)), m_transfer(std::move(transfer)), m_pix_fmt(std::move(pix_fmt)) {}

const std::string& Color::GetPrimaries() const noexcept { return m_prim; }

const std::string& Color::GetMatrix() const noexcept { return m_matrix; }

const std::string& Color::GetTransfer() const noexcept { return m_transfer; }

const std::string& Color::GetPixelFormat() const noexcept { return m_pix_fmt; }

std::list<std::string> Color::GetParameters() const {
	return {
		{ "colorprim=" + m_prim },
		{ "colormatrix=" + m_matrix },
		{ "transfer=" + m_transfer }
	};
}