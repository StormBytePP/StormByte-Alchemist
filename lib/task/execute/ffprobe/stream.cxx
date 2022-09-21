#include "stream.hxx"

using namespace StormByte::VideoConvert;

Task::Execute::FFprobe::Stream::Stream(const Types::path_t& file, const VideoConvert::FFprobe::stream::TYPE& type):FFprobe::Base(file), m_type(type) {}

Task::Execute::FFprobe::Stream::Stream(Types::path_t&& file):FFprobe::Base(std::move(file)) {}

const std::list<std::string> Task::Execute::FFprobe::Stream::BASE_ARGUMENTS { "-show_entries", "stream=codec_name,index,channels:stream_tags=language" };

Task::STATUS Task::Execute::FFprobe::Stream::pre_run_actions() noexcept {
	std::list<std::string> result = BASE_ARGUMENTS;
	result.push_back("-select_streams");

	// Only select real video stream (not cover attachments)
	char type = m_type == VideoConvert::FFprobe::stream::VIDEO ? 'V' : static_cast<char>(m_type);
	result.push_back(std::string(1, std::move(type)));

	m_executables[0].m_arguments = boost::algorithm::join(result, " ");
	return FFprobe::Base::pre_run_actions();
}
