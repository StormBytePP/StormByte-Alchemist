#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class EAC3: public Base {
		public:
			EAC3(unsigned short stream_id);
			EAC3(const EAC3& eac3);
			EAC3& operator=(const EAC3& eac3);
			~EAC3() = default;

			static const std::string EAC3_DEFAULT_ENCODER;
	};
}
