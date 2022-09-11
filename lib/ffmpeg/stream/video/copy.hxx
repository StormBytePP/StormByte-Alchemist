#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Video {
	class Copy: public Base {
		public:
			Copy(unsigned short stream_id);
			Copy(const Copy& copy) = default;
			Copy(Copy&& copy) noexcept = default;
			Copy& operator=(const Copy& copy) = default;
			Copy& operator=(Copy&& copy) noexcept = default;
			~Copy() = default;

			std::list<std::string> ffmpeg_parameters() const override;

		private:
			Copy* copy() const override;
	};
}