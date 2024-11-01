#include <Alchemy/media/video/hdr10.hxx>

#include <string>

using namespace Alchemist::Media::Video;

/** Default values for HDR and color to check and use when metadata is missing in source video **/
const HDR10 HDR10::DEFAULT = { {34000, 16000}, {13250, 34500}, {7500, 3000}, {15635, 16450}, {1, 10000000} };

HDR10::HDR10(const std::pair<unsigned short, unsigned short>& red_point,
			const std::pair<unsigned short, unsigned short>& green_point,
			const std::pair<unsigned short, unsigned short>& blue_point,
			const std::pair<unsigned short, unsigned short>& white_point,
			const std::pair<unsigned short, unsigned int>& luminance):
m_red(red_point), m_green(green_point), m_blue(blue_point), m_white(white_point),
m_luminance(luminance) {}

HDR10::HDR10(const std::pair<unsigned short, unsigned short>& red_point,
			const std::pair<unsigned short, unsigned short>& green_point,
			const std::pair<unsigned short, unsigned short>& blue_point,
			const std::pair<unsigned short, unsigned short>& white_point,
			const std::pair<unsigned short, unsigned int>& luminance,
			const std::pair<unsigned short, unsigned short>& light_level):
m_red(red_point), m_green(green_point), m_blue(blue_point), m_white(white_point),
m_luminance(luminance), m_light_level(light_level) {}

HDR10::HDR10(std::pair<unsigned short, unsigned short>&& red_point,
			std::pair<unsigned short, unsigned short>&& green_point,
			std::pair<unsigned short, unsigned short>&& blue_point,
			std::pair<unsigned short, unsigned short>&& white_point,
			std::pair<unsigned short, unsigned int>&& luminance):
m_red(std::move(red_point)), m_green(std::move(green_point)), m_blue(std::move(blue_point)),
m_white(std::move(white_point)), m_luminance(std::move(luminance)) {}

HDR10::HDR10(std::pair<unsigned short, unsigned short>&& red_point,
			std::pair<unsigned short, unsigned short>&& green_point,
			std::pair<unsigned short, unsigned short>&& blue_point,
			std::pair<unsigned short, unsigned short>&& white_point,
			std::pair<unsigned short, unsigned int>&& luminance,
			std::pair<unsigned short, unsigned short>&& light_level):
m_red(std::move(red_point)), m_green(std::move(green_point)), m_blue(std::move(blue_point)),
m_white(std::move(white_point)), m_luminance(std::move(luminance)), m_light_level(std::move(light_level)) {}

const std::pair<unsigned short, unsigned short>& HDR10::GetRedPoint() const noexcept { return m_red; }

const std::pair<unsigned short, unsigned short>& HDR10::GetGreenPoint() const noexcept { return m_green; }

const std::pair<unsigned short, unsigned short>& HDR10::GetBluePoint() const noexcept { return m_blue; }

const std::pair<unsigned short, unsigned short>& HDR10::GetWhitePoint() const noexcept { return m_white; }

const std::pair<unsigned short, unsigned int>& HDR10::GetLuminance() const noexcept { return m_luminance; }

const std::optional<std::pair<unsigned short, unsigned short>>& HDR10::GetLightLevel() const noexcept { return m_light_level; }

void HDR10::SetLightLevel(const std::pair<unsigned short, unsigned short>& light_level) { m_light_level = light_level; }

void HDR10::SetLightLevel(std::pair<unsigned short, unsigned short>&& light_level) noexcept { m_light_level = std::move(light_level); }

const std::optional<std::string>& HDR10::GetPlusFile() const noexcept { return m_hdr10plus; }

void HDR10::SetPlusFile(const std::string& plusfile) { m_hdr10plus = plusfile; }

void HDR10::SetPlusFile(std::string&& plusfile) noexcept { m_hdr10plus = std::move(plusfile); }

std::list<std::string> HDR10::GetParameters() const {
	std::list<std::string> parameters;
	
	parameters.push_back("master-display=" +
		std::string("G(")	+ std::to_string(m_green.first) 		+ "," + std::to_string(m_green.second) 			+ ")" +
		std::string("B(")	+ std::to_string(m_blue.first)			+ "," + std::to_string(m_blue.second) 			+ ")" +
		std::string("R(")	+ std::to_string(m_red.first)			+ "," + std::to_string(m_red.second) 			+ ")" +
		std::string("WP(")	+ std::to_string(m_white.first)			+ "," + std::to_string(m_white.second) 			+ ")" +
		std::string("L(")	+ std::to_string(m_luminance.first)		+ "," + std::to_string(m_luminance.second) 		+ ")"
	);

	if (m_light_level)
		parameters.push_back("max-cll=" + std::to_string(m_light_level->first) + "," + std::to_string(m_light_level->second));
	
	parameters.push_back("hdr10=1"); // Without this HDR will be ignored

	if (m_hdr10plus)
		parameters.push_back("dhdr10-info=" + *m_hdr10plus);

	return parameters;
}
