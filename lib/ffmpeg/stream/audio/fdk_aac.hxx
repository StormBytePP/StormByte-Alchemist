#pragma once

#include "aac.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class FDKAAC: public AAC {
		public:
			FDKAAC(unsigned short stream_id);
			FDKAAC(const FDKAAC& fdkaac);
			virtual FDKAAC& operator=(const FDKAAC& fdkaac);
			~FDKAAC() = default;

			std::list<std::string> ffmpeg_parameters() const;

		private:
			std::optional<std::string> m_profile;

			static const std::string FDKAAC_DEFAULT_ENCODER;
			static const std::string FDKAAC_DEFAULT_PROFILE;
	};
}