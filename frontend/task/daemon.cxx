#include "daemon.hxx"
#include "application.hxx"
#include "task/execute_ffmpeg.hxx"

#include <iostream>
#include <csignal>
#include <sys/wait.h>

using namespace StormByte::VideoConvert;

Task::Daemon::Daemon():Base() {
	signal(SIGTERM,	signal_handler);
	signal(SIGINT,	signal_handler);
	signal(SIGUSR1,	signal_handler); // Wakeupç

	m_require_logger = true;
	m_require_database = true;
}

Task::Daemon& Task::Daemon::get_instance() {
	static Daemon instance;
	return instance;
}

Task::STATUS Task::Daemon::run(std::shared_ptr<Configuration> config) noexcept {
	if (Base::run(config) == RUNNING) {
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Starting daemon version " + Application::PROGRAM_VERSION);
		m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Resetting previously in process films");
		m_database->reset_processing_films();

		do {
			m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Checking for films to convert...");
			auto film = m_database->get_film_for_process();
			if (film) {
				m_logger->message_line(Utils::Logger::LEVEL_INFO, "Film " + film->get_input_file().string() + " found");
				execute_ffmpeg(*film);
				m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Pausing for " + std::to_string(m_config->get_pause_time()) + " seconds");
				sleep(m_config->get_pause_time());
			}
			else {
				m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "No films found");
				m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Sleeping " + std::to_string(m_config->get_sleep_time()) + " seconds before retrying");
				sleep(m_config->get_sleep_time());
			}
		} while(m_status != HALT_OK && m_status != HALT_ERROR);

		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Stopping daemon...");
		m_status = HALT_OK;
	}
	
	return m_status;
}

void Task::Daemon::execute_ffmpeg(FFmpeg& ffmpeg) {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	const std::filesystem::path full_input_file = *m_config->get_input_folder() / ffmpeg.get_input_file();
	const std::filesystem::path full_work_file = *m_config->get_work_folder() / ffmpeg.get_output_file(); // For FFmpeg out means what for Application is work
	const std::filesystem::path full_output_file = *m_config->get_output_folder() / ffmpeg.get_output_file();

	//m_worker = ffmpeg.exec(*m_config->get_input_folder(), *m_config->get_work_folder(), m_logger);
	Task::ExecuteFFmpeg(ffmpeg).run(m_config);
	int exit_status;
	wait(&exit_status);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	m_worker.reset(); // Worker has finished
	bool status;
	if (exit_status == 0) {
		status = true;
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Conversion for " + ffmpeg.get_input_file().string() + " finished in " + elapsed_time(begin, end));
		if (!std::filesystem::exists(full_output_file.parent_path())) {
			m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Create output path: " + full_output_file.parent_path().string());
			std::filesystem::create_directories(full_output_file.parent_path());
		}
		if (m_config->get_onfinish() == "copy") {
			m_logger->message_line(Utils::Logger::LEVEL_INFO, "Copy: " + full_work_file.string() + " -> " + full_output_file.string());
			std::filesystem::copy_file(full_work_file, full_output_file);
			m_logger->message_line(Utils::Logger::LEVEL_INFO, "Delete work: " + full_work_file.string());
			std::filesystem::remove(full_work_file);
		}
		else {
			m_logger->message_line(Utils::Logger::LEVEL_INFO, "Move: " + full_work_file.string() + " -> " + full_output_file.string());
			std::filesystem::rename(full_work_file, full_output_file);
		}
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Delete input: " + full_input_file.string());
			std::filesystem::remove(full_input_file);
	}
	else {
		status = false;
		m_logger->message_line(Utils::Logger::LEVEL_ERROR, "Conversion for " + ffmpeg.get_input_file().string() + " failed or interrupted!");
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Deleting work file: " + full_work_file.string());
		std::filesystem::remove(full_work_file);
		m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Marking film " + full_work_file.string() + " as unsupported in database");
	}

	m_database->finish_film_process(ffmpeg, status);
	if (ffmpeg.get_group() && m_database->is_group_empty(*ffmpeg.get_group())) {
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Deleting group input folder: " + (*m_config->get_input_folder() / ffmpeg.get_group()->folder).string() + " recursivelly");
		std::filesystem::remove_all(*m_config->get_input_folder() / ffmpeg.get_group()->folder);
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Deleting group work folder: " + (*m_config->get_work_folder() / ffmpeg.get_group()->folder).string() + " recursivelly");
		std::filesystem::remove_all(*m_config->get_work_folder() / ffmpeg.get_group()->folder);
		m_database->delete_group(*ffmpeg.get_group());
	}
}

void Task::Daemon::signal_handler(int signal) {
	auto& task_instance = Daemon::get_instance();
	task_instance.m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Signal " + std::to_string(signal) + " received!");

	switch(signal) {
		case SIGINT:
		case SIGTERM:
			task_instance.m_status = HALT_OK;
			if (task_instance.m_worker)
				kill(*task_instance.m_worker, SIGTERM);
			break;

		case SIGUSR1:
		default:
			// No action as this will only wake up from sleep
			break;
	}
}
