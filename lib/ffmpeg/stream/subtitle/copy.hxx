#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream::Subtitle {
	class Copy: public StormByte::VideoConvert::Stream::Subtitle::Base {
		public:
			Copy(unsigned short stream_id);
			Copy(const Copy& copy);
			Copy(Copy&& copy) noexcept;
			Copy& operator=(const Copy& copy);
			Copy& operator=(Copy&& copy) noexcept;
			~Copy() = default;

		private:
			Copy* copy() const override;
	};
}