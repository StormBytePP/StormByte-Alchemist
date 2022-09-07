#include "opus.hxx"

const std::string StormByte::VideoConvert::Stream::Audio::Opus::OPUS_DEFAULT_ENCODER	= "libopus";

StormByte::VideoConvert::Stream::Audio::Opus::Opus(unsigned short stream_id):StormByte::VideoConvert::Stream::Audio::Base(stream_id, OPUS_DEFAULT_ENCODER) {}

StormByte::VideoConvert::Stream::Audio::Opus::Opus(const Opus& opus):StormByte::VideoConvert::Stream::Audio::Base(opus) {}

StormByte::VideoConvert::Stream::Audio::Opus::Opus(Opus&& opus) noexcept :StormByte::VideoConvert::Stream::Audio::Base(opus) {}

StormByte::VideoConvert::Stream::Audio::Opus& StormByte::VideoConvert::Stream::Audio::Opus::operator=(const Opus& opus) {
	if (&opus != this) {
		StormByte::VideoConvert::Stream::Audio::Base::operator=(opus);
	}
	return *this;
}

StormByte::VideoConvert::Stream::Audio::Opus& StormByte::VideoConvert::Stream::Audio::Opus::operator=(Opus&& opus) noexcept {
	if (&opus != this) {
		StormByte::VideoConvert::Stream::Audio::Base::operator=(opus);
	}
	return *this;
}

StormByte::VideoConvert::Stream::Audio::Opus* StormByte::VideoConvert::Stream::Audio::Opus::copy() const {
	return new Opus(*this);
}