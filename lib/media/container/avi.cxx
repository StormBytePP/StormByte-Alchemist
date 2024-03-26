#include "avi.hxx"

Alchemist::Media::Container::AVI::AVI():Base(Container::AVI, "avi", 2) {
	m_attrs = Attribute::OLD;
}

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::AVI::get_supported_codecs() const {
	return {
		// Video
		Codec::H264, Codec::H265, Codec::MPEG2, Codec::MPEG4, Codec::VP8, Codec::VP9,

		// Audio
		Codec::AAC, Codec::AC3, Codec::DTS, Codec::FLAC, Codec::MP2, Codec::MP3, Codec::OPUS,
	};
}