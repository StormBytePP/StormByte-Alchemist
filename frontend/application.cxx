#include "application.hxx"
#include "task/parse_cli.hxx"

//DEBUG
#include "database/sqlite3.hxx"
#include <exception>
#include "configuration/configuration.hxx"

#include <csignal>
#include <assert.h>

using namespace StormByte::VideoConvert;

Frontend::Application::Application() {
	signal(SIGTERM,		signal_handler);
	signal(SIGINT,		signal_handler);
	signal(SIGUSR1,		signal_handler);
	signal(SIGUSR2,		signal_handler);
}

Frontend::Application& Frontend::Application::get_instance() {
	static Application instance;
	return instance;
}

int Frontend::Application::run(int argc, char** argv) noexcept {
	std::unique_ptr<Task::ParseCLI> parse_cli;
	parse_cli.reset(new Task::ParseCLI(argc, argv));

	if (parse_cli->run() == VideoConvert::Task::HALT_OK) {
		if (parse_cli->get_selected_task())
			m_task = parse_cli->get_selected_task();
		else return 0;
	}
	else
		return 1;

	// If we reached here it means there is a pending tag so...
	parse_cli.reset();

	return m_task->run(m_worker) == VideoConvert::Task::HALT_OK ? 0 : 1;
}

void Frontend::Application::signal_handler(int signal) {
	auto& instance = get_instance();

	switch(signal) {
		case SIGINT:
		case SIGTERM:
			// If instance.m_task is not valid then it is a serios bug, we should not check
			assert(instance.m_task);
			instance.m_task->ask_stop();
			if (instance.m_worker) {
				kill(*instance.m_worker, SIGKILL);
			}
			break;

		case SIGUSR1:
		default:
			// No action as this will only wake up from sleep
			break;
	}
}
