#include "mp4.hxx"

Alchemist::Media::Container::MP4::MP4():Base(Container::MP4, "mp4") { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::MP4::get_supported_codecs() const {
	return {
		// Video
		Codec::AV1, Codec::H264, Codec::H265, Codec::MPEG2, Codec::VP8, Codec::VP9,

		// Audio
		Codec::AAC, Codec::AC3, Codec::DTS, Codec::EAC3, Codec::FLAC, Codec::MP2, Codec::MP3, Codec::OPUS,
	};
}