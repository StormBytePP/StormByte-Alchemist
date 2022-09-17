#include "base.hxx"

using namespace StormByte::VideoConvert;

Task::Base::Base():m_status(STOPPED) {}

Task::STATUS Task::Base::run() noexcept {
	std::optional<pid_t> useless;
	return run(useless);
}

Task::STATUS Task::Base::run(std::optional<pid_t>& worker) noexcept {
	m_start = std::chrono::steady_clock::now();
	STATUS exit_code = do_work(worker);
	m_end = std::chrono::steady_clock::now();
	return exit_code;
}

std::string Task::Base::elapsed_time_string() const {
	/* NOTE: Until C++20's <format> support is complete, I just use this aproach */
	std::string result = "";

	auto elapsed = std::chrono::hh_mm_ss(m_end - m_start);
	auto h = elapsed.hours().count(), m = elapsed.minutes().count(), s = elapsed.seconds().count();

	result += std::to_string(h) + ":";
	if (m < 10) result += "0";
	result += std::to_string(m) + ":";
	if (s < 10) result += "0";
	result += std::to_string(s);

	return result;;
}