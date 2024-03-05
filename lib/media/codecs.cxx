#include "codecs.hxx"

const std::list<StormByte::Alchemist::Media::Codecs::Type> StormByte::Alchemist::Media::Codecs::Available {
	AV1, H264, HEVC, MPEG2, VP8, VP9, MPEG4,			// Video
	AAC, AC3, DTS, EAC3, FLAC, MP2, MP3, OPUS, VORBIS,	// Audio
	BMP, GIF, JPG, PNG, TIFF, WEBP						// Image
};