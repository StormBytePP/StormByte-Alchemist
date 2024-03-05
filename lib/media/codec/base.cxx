#include "base.hxx"
#include <utility>

STVC::Media::Codec::Base::Base(const unsigned short& codec_id): m_codec_id(codec_id) { }

STVC::Media::Codec::Base::Base(unsigned short&& codec_id): m_codec_id(std::move(codec_id)) { }

STVC::Media::Codec::Base::~Base() { }

unsigned short STVC::Media::Codec::Base::get_codec_id() const { return m_codec_id; }

bool STVC::Media::Codec::Base::is_video() const {
	bool result;

	switch(m_codec_id) {
		case STVC::Media::Encoders::AV1:
		case STVC::Media::Encoders::H264:
		case STVC::Media::Encoders::H265:
		case STVC::Media::Encoders::MPEG2:
		case STVC::Media::Encoders::RAV1E:
		case STVC::Media::Encoders::VP8:
		case STVC::Media::Encoders::VP9:
		case STVC::Media::Encoders::XVID:
			result = true;
			break;

		default:
			result = false;
	}

	return result;
}

bool STVC::Media::Codec::Base::is_audio() const {
	bool result;

	switch(m_codec_id) {
		case STVC::Media::Encoders::AAC:
		case STVC::Media::Encoders::AC3:
		case STVC::Media::Encoders::EAC3:
		case STVC::Media::Encoders::FDK_AAC:
		case STVC::Media::Encoders::FLAC:
		case STVC::Media::Encoders::MP3:
		case STVC::Media::Encoders::OPUS:
		case STVC::Media::Encoders::VORBIS:
			result = true;
			break;

		default:
			result = false;
	}

	return result;
}

bool STVC::Media::Codec::Base::is_image() const {
	bool result;

	switch(m_codec_id) {
		case STVC::Media::Encoders::BMP:
		case STVC::Media::Encoders::GIF:
		case STVC::Media::Encoders::JPG:
		case STVC::Media::Encoders::PNG:
		case STVC::Media::Encoders::TIFF:
			result = true;
			break;

		default:
			result = false;
	}

	return result;
}
