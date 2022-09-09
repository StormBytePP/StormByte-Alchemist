#include "opus.hxx"

using namespace StormByte::VideoConvert;

const std::string Stream::Audio::Opus::OPUS_DEFAULT_ENCODER	= "libopus";

Stream::Audio::Opus::Opus(unsigned short stream_id):Stream::Audio::Base(stream_id, OPUS_DEFAULT_ENCODER, Database::Data::AUDIO_OPUS) {}

Stream::Audio::Opus::Opus(const Opus& opus):Stream::Audio::Base(opus) {}

Stream::Audio::Opus::Opus(Opus&& opus) noexcept :Stream::Audio::Base(opus) {}

Stream::Audio::Opus& Stream::Audio::Opus::operator=(const Opus& opus) {
	if (&opus != this) {
		Stream::Audio::Base::operator=(opus);
	}
	return *this;
}

Stream::Audio::Opus& Stream::Audio::Opus::operator=(Opus&& opus) noexcept {
	if (&opus != this) {
		Stream::Audio::Base::operator=(opus);
	}
	return *this;
}

Stream::Audio::Opus* Stream::Audio::Opus::copy() const {
	return new Opus(*this);
}