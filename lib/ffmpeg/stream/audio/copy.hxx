#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class Copy: public Base {
		public:
			Copy(const unsigned short& stream_id);
			Copy(unsigned short&& stream_id);
			Copy(const Copy& copy) = default;
			Copy(Copy&& copy) noexcept = default;
			Copy& operator=(const Copy& copy) = default;
			Copy& operator=(Copy&& copy) noexcept = default;
			~Copy() = default;

		private:
			inline Copy* copy() const override { return new Copy(*this); }
	};
}