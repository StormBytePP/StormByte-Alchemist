#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class Opus: public Base {
		public:
			Opus(unsigned short stream_id);
			Opus(const Opus& opus);
			Opus(Opus&& opus) = default;
			Opus& operator=(const Opus& opus);
			~Opus() = default;

			static const std::string OPUS_DEFAULT_ENCODER;
	};
}
