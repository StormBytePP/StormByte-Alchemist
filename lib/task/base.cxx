#include "base.hxx"

#include <assert.h>

using namespace StormByte::VideoConvert;

Task::Base::Base():m_status(STOPPED) {}

Task::STATUS Task::Base::run() noexcept {
	std::optional<pid_t> useless;
	return run(useless);
}

Task::STATUS Task::Base::run(std::optional<pid_t>& worker) noexcept {
	STATUS status = HALT_ERROR;

	m_start = std::chrono::steady_clock::now();
	if (pre_run_actions() == RUNNING)
		status = do_work(worker);
	// Post run action might change status
	status = post_run_actions(status);
	m_end = std::chrono::steady_clock::now();
	
	assert(status == HALT_OK || status == HALT_ERROR);
	return status;
}

Task::STATUS Task::Base::pre_run_actions() noexcept { return RUNNING; }

Task::STATUS Task::Base::post_run_actions(const STATUS& prev_status) noexcept {
	return prev_status == RUNNING ? HALT_OK : prev_status;
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