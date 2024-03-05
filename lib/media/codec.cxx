#include "codec.hxx"

const std::list<StormByte::Alchemist::Media::Codec::Type> StormByte::Alchemist::Media::Codec::Available() {
	return {
		AV1, H264, H265, MPEG2, VP8, VP9, MPEG4,			// Video
		AAC, AC3, DTS, EAC3, FLAC, MP2, MP3, OPUS, VORBIS,	// Audio
		BMP, GIF, JPG, PNG, TIFF, WEBP						// Image
	};
}

StormByte::Alchemist::Media::Codec::Base::Base(const Codec::Type& codec_type):m_codec_type(codec_type) { }

StormByte::Alchemist::Media::Codec::Base::Base(Codec::Type&& codec_type):m_codec_type(std::move(codec_type)) { }

StormByte::Alchemist::Media::Codec::Type StormByte::Alchemist::Media::Codec::Base::get_codec_type() const {
	return m_codec_type;
}

const std::map<StormByte::Alchemist::Media::Codec::Type, StormByte::Alchemist::Media::Info> DLL_PUBLIC StormByte::Alchemist::Media::Codec::Metadata() {
	return {
		// Video
		{Codec::AV1,		{"AV1",				"AOMedia Video 1"							}},
		{Codec::H264,		{"H264/AVC",		"Advanced Video Coding"						}},
		{Codec::H265,		{"H265/HEVC",		"High Efficiency Video Coding"				}},
		{Codec::MPEG2,		{"MPEG2",			"Moving Picture Experts Group 2"			}},
		{Codec::VP8,		{"VP8",				"Video Processor 8"							}},
		{Codec::VP9,		{"VP9",				"Video Processor 9"							}},
		{Codec::MPEG4,		{"XVID",			"MPEG-4 Video"								}},
		
		//Audio
		{Codec::AAC,		{"AAC",				"Advanced Audio Codec"						}},
		{Codec::AC3,		{"AC-3",			"Dolby AC-3"								}},
		{Codec::DTS,		{"DTS",				"DTS"										}},
		{Codec::EAC3,		{"E-AC3",			"Dolby Digital Plus"						}},
		{Codec::FLAC,		{"FLAC",			"Free Lossless Audio Codec"					}},
		{Codec::MP2,		{"MP2",				"MPEG-1 Audio Layer II"						}},
		{Codec::MP3,		{"MP3",				"MPEG-1 Audio Layer III"					}},
		{Codec::OPUS,		{"OPUS",			"Opus"										}},
		{Codec::VORBIS,		{"VORBIS",			"Vorbis Audio Codec"						}},
		
		//Image
		{Codec::BMP,		{"BMP",				"Microsoft Windows Bitmap Format"			}},
		{Codec::GIF,		{"GIF",				"Graphics Interchange Format"				}},
		{Codec::JPG,		{"JPG",				"Joint Photographic Experts Group"			}},
		{Codec::PNG,		{"PNG",				"Portable Network Graphic"					}},
		{Codec::TIFF,		{"TIFF",			"Tag Image File Format"						}},
		{Codec::WEBP,		{"WEBP",			"WEBP Format"								}}
	};
}