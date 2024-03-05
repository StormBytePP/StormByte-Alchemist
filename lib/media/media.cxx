#include "media.hxx"

const std::list<STVC::Media::Encoders::Encoder> STVC::Media::Encoders::Available {
	// Video
	#ifdef ENABLE_AV1
	AV1,
	#endif
	#ifdef ENABLE_H264
	H264,
	#endif
	#ifdef ENABLE_H265
	H265,
	#endif
	#ifdef ENABLE_MPEG2
	MPEG2,
	#endif
	#ifdef ENABLE_RAV1E
	RAV1E,
	#endif
	#ifdef ENABLE_VPX
	VP8,
	VP9,
	#endif
	#ifdef ENABLE_XVID
	XVID,
	#endif

	// Audio
	#ifdef ENABLE_AAC
	AAC,
	#endif
	#ifdef ENABLE_AC3
	AC3,
	#endif
	#ifdef ENABLE_EAC3
	EAC3,
	#endif
	#ifdef ENABLE_FDK_AAC
	FDK_AAC,
	#endif
	#ifdef ENABLE_FLAC
	FLAC,
	#endif
	#ifdef ENABLE_MP3
	MP3,
	#endif
	#ifdef ENABLE_OPUS
	OPUS,
	#endif
	#ifdef ENABLE_VORBIS
	VORBIS,
	#endif

	//Image
	BMP,
	GIF,
	JPG,
	PNG,
	TIFF
};

const std::map<STVC::Media::Encoders::Encoder, std::pair<std::string, std::string>> STVC::Media::Encoders::Names {
	//Video
	{AV1,		{"AV1",				"AOMedia Video 1"							}},
	{H264,		{"AVC/H264",		"Advanced Video Coding"						}},
	{H265,		{"HEVC/H265",		"High Efficiency Video Coding"				}},
	{MPEG2,		{"MPEG2",			"Moving Picture Experts Group 2"			}},
	{RAV1E,		{"AV1",				"RAV1E AOMedia Video 1"						}},
	{VP8,		{"VP8",				"Video Processor 8"							}},
	{VP9,		{"VP9",				"Video Processor 9"							}},
	{XVID,		{"XVID",			"MPEG-4 Video"								}},
	
	//Audio
	{AAC,		{"AAC",				"Advanced Audio Codec"						}},
	{AC3,		{"AC-3",			"Dolby AC-3"								}},
	{DTS,		{"DTS",				"DTS"										}},
	{EAC3,		{"E-AC3",			"Dolby Digital Plus"						}},
	{FDK_AAC,	{"Fraunhoffer AAC",	"Fraunhoffer Advanced Audio Codec"			}},
	{FLAC,		{"FLAC",			"Free Lossless Audio Codec"					}},
	{MP3,		{"MP3",				"MPEG-1 Audio Layer III"					}},
	{OPUS,		{"OPUS",			"Opus"										}},
	{VORBIS,	{"VORBIS",			"Vorbis Audio Codec"						}},
	
	//Image
	{BMP,		{"BMP",				"Microsoft Windows Bitmap Format"			}},
	{GIF,		{"GIF",				"Graphics Interchange Format"				}},
	{JPG,		{"JPG",				"Joint Photographic Experts Group"			}},
	{PNG,		{"PNG",				"Portable Network Graphic"					}},
	{TIFF,		{"TIFF",			"Tag Image File Format"						}}
};

bool STVC::Media::Encoders::is_video(const Encoder& enc) const {
	bool result;

	switch(enc) {
		case AV1:
		case H264:
		case H265:
		case MPEG2:
		case RAV1E:
		case VP8:
		case VP9:
		case XVID:
			result = true;
			break;

		default:
			result = false;
	}

	return result;
}

bool STVC::Media::Encoders::is_audio(const Encoder& enc) const {
	bool result;

	switch(enc) {
		case AAC:
		case AC3:
		case EAC3:
		case FDK_AAC:
		case FLAC:
		case MP3:
		case OPUS:
		case VORBIS:
			result = true;
			break;

		default:
			result = false;
	}

	return result;
}

bool STVC::Media::Encoders::is_image(const Encoder& enc) const {
	bool result;

	switch(enc) {
		case BMP:
		case GIF:
		case JPG:
		case PNG:
		case TIFF:
			result = true;
			break;

		default:
			result = false;
	}

	return result;
}
