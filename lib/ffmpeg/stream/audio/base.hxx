#pragma once

#include "../base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class Base: public StormByte::VideoConvert::Stream::Base {
		public:
			Base(unsigned short stream_id, const std::string& encoder);
			Base(const Base& base);
			Base(Base&& base) = default;
			Base& operator=(const Base& base);
			virtual ~Base() = default;
			
			virtual std::list<std::string> ffmpeg_parameters() const;
	};
}