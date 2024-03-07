#include "codec.hxx"
#include "codec/audio/aac.hxx"
#include "codec/audio/ac3.hxx"
#include "codec/audio/dts.hxx"
#include "codec/audio/eac3.hxx"
#include "codec/audio/flac.hxx"
#include "codec/audio/mp2.hxx"
#include "codec/audio/mp3.hxx"
#include "codec/audio/opus.hxx"
#include "codec/audio/vorbis.hxx"

Alchemist::Media::Codec::Base::Base(const Codec::Type& codec_type):m_codec_type(codec_type) { }

Alchemist::Media::Codec::Base::Base(Codec::Type&& codec_type):m_codec_type(std::move(codec_type)) { }

Alchemist::Media::Codec::Type Alchemist::Media::Codec::Base::get_codec_type() const {
	return m_codec_type;
}

std::shared_ptr<Alchemist::Media::Codec::Base> Alchemist::Media::Codec::Instance(const Codec::Type& codec) {
	std::shared_ptr<Codec::Base> result;
	
	switch(codec) {
		case Codec::AAC:
			result.reset(new Codec::Audio::AAC());
			break;

		case Codec::AC3:
			result.reset(new Codec::Audio::AC3());
			break;

		case Codec::DTS:
			result.reset(new Codec::Audio::DTS());
			break;

		case Codec::EAC3:
			result.reset(new Codec::Audio::EAC3());
			break;

		case Codec::FLAC:
			result.reset(new Codec::Audio::FLAC());
			break;

		case Codec::MP2:
			result.reset(new Codec::Audio::MP2());
			break;

		case Codec::MP3:
			result.reset(new Codec::Audio::MP3());
			break;

		case Codec::OPUS:
			result.reset(new Codec::Audio::OPUS());
			break;

		case Codec::VORBIS:
			result.reset(new Codec::Audio::VORBIS());
			break;


	}

	return result;
}