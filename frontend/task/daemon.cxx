#include "daemon.hxx"
#include "definitions.h"
#include "task/execute/ffmpeg/convert.hxx"

#include <iostream>

using namespace StormByte::VideoConvert;

Frontend::Task::Daemon::Daemon(Types::config_t config, std::optional<pid_t>& worker):VideoConvert::Task::Config::Base(config, VideoConvert::Task::Config::REQUIRE_LOGGER | VideoConvert::Task::Config::REQUIRE_DATABASE), m_worker(&worker) {}

Task::STATUS Frontend::Task::Daemon::do_work(std::optional<pid_t>&) noexcept {
	m_logger->message_line(Utils::Logger::LEVEL_INFO, "Starting daemon version " + std::string(PROGRAM_VERSION));
	m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Resetting previously in process films");
	m_database->reset_processing_films();

	do {
		m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Checking for films to convert...");
		auto film = m_database->get_film_for_process();
		if (film) {
			m_logger->message_line(Utils::Logger::LEVEL_INFO, "Film " + film->get_input_file().string() + " found");
			execute_ffmpeg(std::move(*film));
			// Only sleep if process is to be continued (not killed by a signal)
			if (m_status != VideoConvert::Task::HALTED) {
				m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Pausing for " + std::to_string(m_config->get_pause_time()) + " seconds");
				sleep(m_config->get_pause_time());
			}
		}
		else {
			m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "No films found");
			m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Sleeping " + std::to_string(m_config->get_sleep_time()) + " seconds before retrying");
			sleep(m_config->get_sleep_time());
		}
	} while(m_status != VideoConvert::Task::HALTED);

	m_logger->message_line(Utils::Logger::LEVEL_INFO, "Stopping daemon...");
	
	return VideoConvert::Task::HALT_OK;
}

void Frontend::Task::Daemon::execute_ffmpeg(FFmpeg&& ffmpeg) const {
	const Types::path_t full_input_file = *m_config->get_input_folder() / ffmpeg.get_input_file();
	const Types::path_t full_work_file = *m_config->get_work_folder() / ffmpeg.get_output_file(); // For FFmpeg out means what for Application is work
	const Types::path_t full_output_file = *m_config->get_output_folder() / ffmpeg.get_output_file();

	// We need to be sure that the output folder exists so we try to create before running in that case
	if (!std::filesystem::exists(full_work_file.parent_path())) {
		m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Create work path: " + full_work_file.parent_path().string());
		std::filesystem::create_directories(full_work_file.parent_path());
	}
	VideoConvert::Task::Execute::FFmpeg::Convert task_ffmpeg = VideoConvert::Task::Execute::FFmpeg::Convert(std::move(ffmpeg), *m_config->get_input_folder(), *m_config->get_work_folder());
	VideoConvert::Task::STATUS convert_status = task_ffmpeg.run(*m_worker);
	
	if (convert_status == VideoConvert::Task::HALT_OK) {
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Conversion for " + ffmpeg.get_input_file().string() + " finished in " + task_ffmpeg.elapsed_time_string());
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
		m_logger->message_line(Utils::Logger::LEVEL_ERROR, "Conversion for " + ffmpeg.get_input_file().string() + " failed or interrupted!");
		if (!task_ffmpeg.get_stderr().empty())
			m_logger->message_line(Utils::Logger::LEVEL_ERROR, "stderr contains:\n" + task_ffmpeg.get_stderr());
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Deleting work file: " + full_work_file.string());
		std::filesystem::remove(full_work_file);
		m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Marking film " + full_work_file.string() + " as unsupported in database");
	}

	m_database->finish_film_process(ffmpeg, convert_status == VideoConvert::Task::HALT_OK);
	if (ffmpeg.get_group() && m_database->is_group_empty(*ffmpeg.get_group())) {
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Deleting group input folder: " + (*m_config->get_input_folder() / ffmpeg.get_group()->folder).string() + " recursivelly");
		std::filesystem::remove_all(*m_config->get_input_folder() / ffmpeg.get_group()->folder);
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Deleting group work folder: " + (*m_config->get_work_folder() / ffmpeg.get_group()->folder).string() + " recursivelly");
		std::filesystem::remove_all(*m_config->get_work_folder() / ffmpeg.get_group()->folder);
		m_database->delete_group(*ffmpeg.get_group());
	}
}
