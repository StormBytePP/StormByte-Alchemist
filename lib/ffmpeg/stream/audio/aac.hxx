#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class AAC: public Base {
		public:
			AAC(unsigned short stream_id);
			AAC(const AAC& aac);
			AAC& operator=(const AAC& aac);
			~AAC() = default;
			
			std::list<std::string> ffmpeg_parameters() const;

		private:
			std::optional<std::string> m_profile;

			static const std::string AAC_DEFAULT_ENCODER;
			static const std::string AAC_DEFAULT_PROFILE;
	};
}
