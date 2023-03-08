#pragma once

#include "task/cli/base.hxx"
#include "configuration/base.hxx"
#include "utils/logger.hxx"
#include "database/sqlite3.hxx"
#include "ffmpeg/ffmpeg.hxx"

namespace StormByte::VideoConvert::Frontend::Task {
	class Daemon: public VideoConvert::Task::CLI::Base {
		public:
			Daemon() = default;
			Daemon(const Daemon& daemon) = delete;
			Daemon(Daemon&& daemon) noexcept = default;
			Daemon& operator=(const Daemon& daemon) = delete;
			Daemon& operator=(Daemon&& daemon) noexcept = delete;
			~Daemon() noexcept = default;

		private:
			VideoConvert::Task::STATUS pre_run_actions() noexcept override;
			VideoConvert::Task::STATUS post_run_actions(const VideoConvert::Task::STATUS&) noexcept override;
			VideoConvert::Task::STATUS do_work(std::optional<pid_t>&) noexcept override;
			VideoConvert::Task::STATUS execute_ffmpeg(FFmpeg&& ffmpeg, std::optional<pid_t>&) const;

			Types::logger_t m_logger;
			Types::database_t m_database;
	};
}
