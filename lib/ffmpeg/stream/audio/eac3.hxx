#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class EAC3: public Base {
		public:
			EAC3(const unsigned short& stream_id);
			EAC3(unsigned short&& stream_id);
			EAC3(const EAC3& eac3) = default;
			EAC3(EAC3&& eac3) noexcept = default;
			EAC3& operator=(const EAC3& eac3) = default;
			EAC3& operator=(EAC3&& eac3) noexcept = default;
			~EAC3() = default;

		private:
			static const std::string EAC3_DEFAULT_ENCODER;

			inline EAC3* copy() const override { return new EAC3(*this); }
	};
}
