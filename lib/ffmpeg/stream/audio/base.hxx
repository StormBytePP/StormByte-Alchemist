#pragma once

#include "../base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class Base: public StormByte::VideoConvert::Stream::Base {
		public:
			Base(unsigned short stream_id, const std::string& encoder, Database::Data::stream_codec codec);
			Base(const Base& base);
			Base(Base&& base) noexcept;
			Base& operator=(const Base& base);
			Base& operator=(Base&& base) noexcept;
			virtual ~Base() = default;
	};
}