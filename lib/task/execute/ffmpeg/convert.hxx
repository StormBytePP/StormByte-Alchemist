#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Task::Execute::FFmpeg {
	class Convert: public FFmpeg::Base {
		public:
			Convert(const VideoConvert::FFmpeg&, const Types::path_t& in, const Types::path_t& out);
			Convert(VideoConvert::FFmpeg&&, Types::path_t&& in, Types::path_t&& out);
			Convert(const Convert&) = default;
			Convert(Convert&&) noexcept = default;
			Convert& operator=(const Convert&) = default;
			Convert& operator=(Convert&&) noexcept = default;
			~Convert() noexcept = default;

		private:
			void pre_run_actions() noexcept override;

			Types::path_t m_inpath, m_outpath;
	};
}
