#include "ignore.hxx"
#include "../../database/data.hxx"

const unsigned int StormByte::VideoConvert::Stream::Ignore::INVALID_CODEC_ID = StormByte::VideoConvert::Database::Data::INVALID_CODEC;
const std::string StormByte::VideoConvert::Stream::Ignore::INVALID_CODEC_NAME = "INVALID-666";

StormByte::VideoConvert::Stream::Ignore::Ignore():Base(INVALID_CODEC_ID, INVALID_CODEC_NAME) {}

StormByte::VideoConvert::Stream::Ignore::Ignore(const Ignore& codec): Base(codec) {}

StormByte::VideoConvert::Stream::Ignore::~Ignore() {}

StormByte::VideoConvert::Stream::Ignore& StormByte::VideoConvert::Stream::Ignore::operator=(const Ignore& codec) {
	if (&codec != this) {
		StormByte::VideoConvert::Stream::Base::operator=(*this);
	}
	return *this;
}

std::list<std::string> StormByte::VideoConvert::Stream::Ignore::ffmpeg_parameters() const {
	return std::list<std::string>();
}
