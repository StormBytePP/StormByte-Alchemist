#pragma once

#include "task/base.hxx"
#include "ffmpeg/ffmpeg.hxx"

namespace StormByte::VideoConvert::Task {
	class Daemon: public Base {
		public:
			Daemon(const Daemon& daemon) = delete;
			Daemon(Daemon&& daemon) noexcept = delete;
			Daemon& operator=(const Daemon& daemon) = delete;
			Daemon& operator=(Daemon&& daemon) noexcept = delete;
			~Daemon() noexcept = default;

			static Daemon& get_instance();

			STATUS run(Types::config_t config) noexcept override;

		private:
			Daemon();
			void execute_ffmpeg(FFmpeg& ffmpeg);
			static void signal_handler(int);

			std::optional<pid_t> m_worker;
	};
}