#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Stream {
	class Ignore: public Base {
		public:
			Ignore();
			Ignore(const Ignore& codec_ignore);
			Ignore& operator=(const Ignore& codec_ignore);
			~Ignore();

			std::list<std::string> ffmpeg_parameters() const;

		private:
			static const unsigned int INVALID_CODEC_ID;
			static const std::string INVALID_CODEC_NAME;
	};
}