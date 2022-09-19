#pragma once

#include "task/config/base.hxx"
#include "ffmpeg/ffmpeg.hxx"

namespace StormByte::VideoConvert::Frontend::Task {
	class Daemon: public VideoConvert::Task::Config::Base {
		public:
			Daemon(Types::config_t config);
			Daemon(const Daemon& daemon) = default;
			Daemon(Daemon&& daemon) noexcept = default;
			Daemon& operator=(const Daemon& daemon) = default;
			Daemon& operator=(Daemon&& daemon) noexcept = default;
			~Daemon() noexcept = default;

		private:
			VideoConvert::Task::STATUS do_work(std::optional<pid_t>&) noexcept override;
			VideoConvert::Task::STATUS execute_ffmpeg(FFmpeg&& ffmpeg, std::optional<pid_t>&) const;
	};
}
