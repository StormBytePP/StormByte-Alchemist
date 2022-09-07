#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class Opus: public Base {
		public:
			Opus(unsigned short stream_id);
			Opus(const Opus& opus);
			Opus(Opus&& opus) noexcept;
			Opus& operator=(const Opus& opus);
			Opus& operator=(Opus&& opus) noexcept;
			~Opus() = default;

		private:
			static const std::string OPUS_DEFAULT_ENCODER;

			Opus* copy() const override;
	};
}
