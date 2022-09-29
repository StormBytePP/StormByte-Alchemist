#include "daemon.hxx"
#include "definitions.h"
#include "configuration/configuration.hxx"
#include "task/execute/ffmpeg/convert.hxx"

using namespace StormByte::VideoConvert;

Task::STATUS Frontend::Task::Daemon::pre_run_actions() noexcept {
	VideoConvert::Task::STATUS status = VideoConvert::Task::RUNNING;

	assert(m_config);
	try {
		const Frontend::Configuration* const config = dynamic_cast<Frontend::Configuration*>(m_config.get());
		m_logger.reset(new Utils::Logger(*config->get_log_file(), static_cast<Utils::Logger::LEVEL>(*config->get_log_level())));
		m_database.reset(new Database::SQLite3(*config->get_database_file(), m_logger));
	}
	catch (const std::exception& e) {
		std::cerr << red(e.what()) << std::endl;
		status = VideoConvert::Task::HALT_ERROR;
	}

	return status;
}

Task::STATUS Frontend::Task::Daemon::post_run_actions(const VideoConvert::Task::STATUS& status) noexcept {
	m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Daemon ran during " + elapsed_time_string() + " and was stopped gracefully");

	return VideoConvert::Task::CLI::Base::post_run_actions(status);
}

Task::STATUS Frontend::Task::Daemon::do_work(std::optional<pid_t>& worker) noexcept {
	const Frontend::Configuration* const config = dynamic_cast<Frontend::Configuration*>(m_config.get());
	m_logger->message_line(Utils::Logger::LEVEL_INFO, "Starting daemon version " + std::string(PROGRAM_VERSION));
	m_logger->message_line(Utils::Logger::LEVEL_DEBUG, "Resetting previously in process films");
	m_database->reset_processing_films();

	do {
		m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Checking for films to convert...");
		auto film = m_database->get_film_for_process();
		if (film) {
			m_logger->message_line(Utils::Logger::LEVEL_INFO, "Film " + film->get_input_file().string() + " found");
			auto convert_status = execute_ffmpeg(std::move(*film), worker);
			// Only sleep if process is to be continued (not killed by a signal)
			if (m_status != VideoConvert::Task::HALT_ERROR && convert_status != VideoConvert::Task::HALT_ERROR) {
				m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Pausing for " + std::to_string(config->get_pause_time()) + " seconds");
				sleep(config->get_pause_time());
			}
		}
		else {
			m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "No films found");
			m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Sleeping " + std::to_string(config->get_sleep_time()) + " seconds before retrying");
			sleep(config->get_sleep_time());
		}
	} while(m_status != VideoConvert::Task::HALTED);

	m_logger->message_line(Utils::Logger::LEVEL_INFO, "Stopping daemon...");
	
	return VideoConvert::Task::HALT_OK;
}

StormByte::VideoConvert::Task::STATUS Frontend::Task::Daemon::execute_ffmpeg(FFmpeg&& ffmpeg, std::optional<pid_t>& worker) const {
	const Frontend::Configuration* const config = dynamic_cast<Frontend::Configuration*>(m_config.get());
	const Types::path_t full_input_file = *config->get_input_folder() / ffmpeg.get_input_file();
	const Types::path_t full_work_file = *config->get_work_folder() / ffmpeg.get_output_file(); // For FFmpeg out means what for Application is work
	const Types::path_t full_output_file = *config->get_output_folder() / ffmpeg.get_output_file();

	// We need to be sure that the output folder exists so we try to create before running in that case
	if (!std::filesystem::exists(full_work_file.parent_path())) {
		m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Create work path: " + full_work_file.parent_path().string());
		std::filesystem::create_directories(full_work_file.parent_path());
	}
	VideoConvert::Task::Execute::FFmpeg::Convert task_ffmpeg = VideoConvert::Task::Execute::FFmpeg::Convert(std::move(ffmpeg), *config->get_input_folder(), *config->get_work_folder());
	task_ffmpeg.set_logger(m_logger);
	VideoConvert::Task::STATUS convert_status = task_ffmpeg.run(worker);
	
	if (convert_status == VideoConvert::Task::HALT_OK) {
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Conversion for " + ffmpeg.get_input_file().string() + " finished in " + task_ffmpeg.elapsed_time_string());
		if (!std::filesystem::exists(full_output_file.parent_path())) {
			m_logger->message_line(Utils::Logger::LEVEL_NOTICE, "Create output path: " + full_output_file.parent_path().string());
			std::filesystem::create_directories(full_output_file.parent_path());
		}
		if (config->get_onfinish() == "copy") {
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
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Deleting group input folder: " + (*config->get_input_folder() / ffmpeg.get_group()->folder).string() + " recursivelly");
		std::filesystem::remove_all(*config->get_input_folder() / ffmpeg.get_group()->folder);
		m_logger->message_line(Utils::Logger::LEVEL_INFO, "Deleting group work folder: " + (*config->get_work_folder() / ffmpeg.get_group()->folder).string() + " recursivelly");
		std::filesystem::remove_all(*config->get_work_folder() / ffmpeg.get_group()->folder);
		m_database->delete_group(*ffmpeg.get_group());
	}

	return convert_status;
}
