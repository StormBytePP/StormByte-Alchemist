#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class FDKAAC: public Base {
		public:
			FDKAAC(const unsigned short& stream_id);
			FDKAAC(unsigned short&& stream_id);
			FDKAAC(const FDKAAC& fdkaac) = default;
			FDKAAC(FDKAAC&& fdkaac) noexcept = default;
			FDKAAC& operator=(const FDKAAC& fdkaac) = default;
			FDKAAC& operator=(FDKAAC&& fdkaac) noexcept = default;
			~FDKAAC() = default;

			std::list<std::string> ffmpeg_parameters() const override;

		private:
			std::optional<std::string> m_profile;
			static const std::string FDKAAC_DEFAULT_ENCODER;
			static const std::string FDKAAC_DEFAULT_PROFILE;

			inline FDKAAC* copy() const override { return new FDKAAC(*this); }
	};
}
