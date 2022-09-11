#pragma once

#include "../base.hxx"

namespace StormByte::VideoConvert::Stream::Subtitle {
	class Base: public StormByte::VideoConvert::Stream::Base {
		public:
			Base(unsigned short stream_id, const std::string& encoder, Database::Data::stream_codec codec);
			Base(const Base& base) = default;
			Base(Base&& base) noexcept = default;
			Base& operator=(const Base& base) = default;
			Base& operator=(Base&& base) noexcept = default;
			virtual ~Base() = default;
	};
}