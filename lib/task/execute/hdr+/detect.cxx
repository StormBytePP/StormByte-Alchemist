#include "detect.hxx"

using namespace StormByte::VideoConvert;

Task::Execute::HDRPlus::Detect::Detect(const Types::path_t& file):Task::Execute::HDRPlus::Base(file) {
	m_executables[1].m_arguments = "--verify extract -";
}

Task::Execute::HDRPlus::Detect::Detect(Types::path_t&& file):Task::Execute::HDRPlus::Base(std::move(file)) {
	m_executables[1].m_arguments = "--verify extract -";
}
