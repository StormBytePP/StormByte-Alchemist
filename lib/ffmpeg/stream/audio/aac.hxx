#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class AAC: public Base {
		public:
			AAC(unsigned short stream_id);
			AAC(const AAC& aac);
			AAC(AAC& aac) = default;
			virtual AAC& operator=(const AAC& aac);
			~AAC() = default;

		private:
			static const std::string AAC_DEFAULT_ENCODER;
	};
}
