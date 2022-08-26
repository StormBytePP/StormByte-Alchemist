#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class AC3: public Base {
		public:
			AC3(unsigned short stream_id);
			AC3(const AC3& ac3);
			AC3(AC3&& ac3) = default;
			AC3& operator=(const AC3& ac3);
			~AC3() = default;
			StormByte::VideoConvert::Stream::Base* copy() const;

			static const std::string AC3_DEFAULT_ENCODER;
	};
}
