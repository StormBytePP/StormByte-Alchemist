#include "mkv.hxx"

Alchemist::Media::Container::MKV::MKV():Base(Container::MKV, "mkv") { }

const std::list<Alchemist::Media::Codec::Type> Alchemist::Media::Container::MKV::get_supported_codecs() const {
	return {
		// Video
		Codec::AV1, Codec::H264, Codec::H265, Codec::MPEG2, Codec::MPEG4, Codec::VP8, Codec::VP9,

		// Audio
		Codec::AAC, Codec::AC3, Codec::DTS, Codec::EAC3, Codec::FLAC, Codec::MP2, Codec::MP3, Codec::OPUS, Codec::VORBIS,
	};
}