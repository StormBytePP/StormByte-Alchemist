#include "execute_ffmpeg.hxx"
#include "application.hxx"

#include <boost/algorithm/string/join.hpp>

using namespace StormByte::VideoConvert;

const std::list<const char*> Task::ExecuteFFmpeg::FFMPEG_INIT_OPTIONS = std::list<const char*>({ "-hide_banner", "-y", "-map_metadata", "0", "-map_chapters", "0" });

Task::ExecuteFFmpeg::ExecuteFFmpeg(const FFmpeg& ffmpeg):Execute(Application::FFMPEG_EXECUTABLE), m_ffmpeg(ffmpeg) {}

Task::ExecuteFFmpeg::ExecuteFFmpeg(FFmpeg&& ffmpeg):Execute(Application::FFMPEG_EXECUTABLE), m_ffmpeg(std::move(ffmpeg)) {}

void Task::ExecuteFFmpeg::set_arguments() {
	std::list<std::string> result { "-i \"" + std::string(*m_config->get_input_folder() / m_ffmpeg.get_input_file()) + "\""};
	result.insert(result.end(), FFMPEG_INIT_OPTIONS.begin(), FFMPEG_INIT_OPTIONS.end());

	for (auto it = m_ffmpeg.get_streams().begin(); it != m_ffmpeg.get_streams().end(); it++) {
		auto parameters = (*it)->ffmpeg_parameters();
		result.insert(result.end(), parameters.begin(), parameters.end());
	}

	if (m_ffmpeg.get_title()) {
		result.push_back("-metadata"); result.push_back("title=\"" + *m_ffmpeg.get_title() + "\"");
	}
	else {
		result.push_back("-metadata"); result.push_back("title=");
	}

	result.push_back("-metadata:s:v"); result.push_back("encoder=\"" + Application::PROGRAM_NAME + " " + Application::PROGRAM_VERSION + " ( " + Application::PROJECT_URI + " )\"" );

	result.push_back("\"" + std::string(*m_config->get_work_folder() / m_ffmpeg.get_output_file()) + "\"");

	m_arguments = boost::algorithm::join(result, " ");
}
