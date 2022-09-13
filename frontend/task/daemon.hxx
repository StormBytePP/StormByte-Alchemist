#pragma once

#include "base.hxx"
#include "ffmpeg/ffmpeg.hxx"

namespace StormByte::VideoConvert::Task {
	class Daemon: public Base {
		public:
			Daemon(const Daemon& daemon) = default;
			Daemon(Daemon&& daemon) noexcept = default;
			Daemon& operator=(const Daemon& daemon) = default;
			Daemon& operator=(Daemon&& daemon) noexcept = default;
			~Daemon() noexcept = default;

			static Daemon& get_instance();

			STATUS run(std::shared_ptr<Configuration> config) noexcept override;

		private:
			Daemon();
			void execute_ffmpeg(FFmpeg& ffmpeg);
			static void signal_handler(int);

			std::optional<pid_t> m_worker;
	};
}