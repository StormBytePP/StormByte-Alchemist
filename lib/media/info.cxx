#include "info.hxx"

using namespace Alchemist;

const std::list<Media::Info::Item> Media::Info::Codec::All = {
	// Video
	{	Media::Codec::AV1,		"av1",		"AOMedia Video 1"							},
	{	Media::Codec::H264,		"h264",		"Advanced Video Coding"						},
	{	Media::Codec::H265,		"hevc",		"High Efficiency Video Coding"				},
	{	Media::Codec::MPEG2,	"mpeg2",	"Moving Picture Experts Group 2"			},
	{	Media::Codec::VP8,		"vp8",		"Video Processor 8"							},
	{	Media::Codec::VP9,		"vp9",		"Video Processor 9"							},
	{	Media::Codec::MPEG4,	"mpeg4",	"MPEG-4 Video"								},
	
	//Audio
	{	Media::Codec::AAC,		"aac",		"Advanced Audio Codec"						},
	{	Media::Codec::AC3,		"ac3",		"Dolby AC-3"								},
	{	Media::Codec::DTS,		"dts",		"DTS"										},
	{	Media::Codec::EAC3,		"eac3",		"Dolby Digital Plus"						},
	{	Media::Codec::FLAC,		"flac",		"Free Lossless Audio Codec"					},
	{	Media::Codec::MP2,		"mp3",		"MPEG-1 Audio Layer II"						},
	{	Media::Codec::MP3,		"mp3",		"MPEG-1 Audio Layer III"					},
	{	Media::Codec::OPUS,		"opus",		"Opus"										},
	{	Media::Codec::VORBIS,	"vorbis",	"Vorbis Audio Codec"						},

	//Image
	{	Media::Codec::BMP,		"bmp",		"Microsoft Windows Bitmap Format"			},
	{	Media::Codec::GIF,		"gif",		"Graphics Interchange Format"				},
	{	Media::Codec::JPG,		"jpg",		"Joint Photographic Experts Group"			},
	{	Media::Codec::PNG,		"png",		"Portable Network Graphic"					},
	{	Media::Codec::TIFF,		"tiff",		"Tag Image File Format"						},
	{	Media::Codec::WEBP,		"webp",		"WEBP Format"								}
};

const std::list<Media::Codec::Type> Media::Info::Codec::Available = {
	Media::Codec::AV1,	Media::Codec::H264,	Media::Codec::H265,	Media::Codec::MPEG2,Media::Codec::VP8,	Media::Codec::VP9,	Media::Codec::MPEG4,											// Video
	Media::Codec::AAC,	Media::Codec::AC3,	Media::Codec::DTS,	Media::Codec::EAC3,	Media::Codec::FLAC,	Media::Codec::MP2,	Media::Codec::MP3,	Media::Codec::OPUS,	Media::Codec::VORBIS,	// Audio
	#ifdef ENABLE_IMAGE_PROCESS
	Media::Codec::BMP,	Media::Codec::GIF,	Media::Codec::JPG,	Media::Codec::PNG,	Media::Codec::TIFF,	Media::Codec::WEBP																	// Image
	#endif
};

const std::list<Media::Info::Item> Media::Info::Container::All = {
	// Video
	{ Media::Container::AVI,	"avi",						"AVI (Audio Video Interleaved)" },
	{ Media::Container::MKV,	"matroska,webm",			"Matroska / WebM" },
	{ Media::Container::MP4,	"mov,mp4,m4a,3gp,3g2,mj2",	"QuickTime / MOV" },
	{ Media::Container::OGG,	"ogg",						"Ogg Vorbis" },
	{ Media::Container::WMV,	"asf",						"ASF (Advanced / Active Streaming Format)" },

	// Audio
	{ Media::Container::AAC,	"aac",						"raw ADTS AAC (Advanced Audio Coding)" },
	{ Media::Container::DTS,	"dts",						"raw DTS" },
	{ Media::Container::MP3,	"mp3",						"MP2/3 (MPEG audio layer 2/3)" },
	{ Media::Container::OPUS,	"ogg",						"Opus" },
};

const std::list<Media::Container::Type> Media::Info::Container::Available = {
	Media::Container::AVI, Media::Container::MKV, Media::Container::MP4, Media::Container::OGG, Media::Container::WMV, // Video
	Media::Container::AAC, Media::Container::DTS, Media::Container::MP3, Media::Container::OPUS // Audio
};

const std::list<Media::Info::Item> Media::Info::Decoder::All = {
	// Video
	{Media::Decoder::AV1_DAV1D,			"libdav1d",			"DAV1D"					},
	{Media::Decoder::AV1_LIBAOM,		"libaom-av1",		"AOM AV1"				},
	{Media::Decoder::AV1_CUVID,			"av1_cuvid",		"CuVid AV1"				},
	{Media::Decoder::H264_OPENH264,		"libopenh264",		"OpenH264"				},
	{Media::Decoder::H264_CUVID,		"h264_cuvid",		"CuVid H264"			},
	{Media::Decoder::H265_CUVID,		"hevc_cuvid",		"CuVid H265(HEVC)"		},
	{Media::Decoder::MPEG2_CUVID,		"mpeg2_cuvid",		"CuVid MPEG-2"			},
	{Media::Decoder::VP8_LIBVPX,		"libvpx",			"VPX VP8"				},
	{Media::Decoder::VP8_CUVID,			"vp8_cuvid",		"CuVid VP8"				},
	{Media::Decoder::VP9_LIBVPX,		"libvpx-vp9",		"VPX VP9"				},
	{Media::Decoder::VP9_CUVID,			"vp9_cuvid",		"CuVid VP9"				},
	{Media::Decoder::MPEG4_CUVID,		"mpeg4_cuvid",		"CuVid MPEG-4"			},

	// Audio
	{Media::Decoder::AAC_FRAUNHOFFER,	"libfdk_aac",		"Fraunhoffer AAC"		},
	{Media::Decoder::OPUS_LIBOPUS,		"libopus",			"LibOpus"				},
	{Media::Decoder::VORBIS_LIBVORBIS,	"libvorbis",		"LibVorbis"				},

	// Image
};

const std::list<Media::Decoder::Type> Media::Info::Decoder::Available = {
	// Video
	#ifdef ENABLE_DAV1D
	Media::Decoder::AV1_DAV1D,
	#endif
	#ifdef ENABLE_LIBAOM
	Media::Decoder::AV1_LIBAOM,
	#endif
	#ifdef ENABLE_CUDA
	Media::Decoder::AV1_CUVID,
	#endif
	#ifdef ENABLE_OPENH264
	Media::Decoder::H264_OPENH264,
	#endif
	#ifdef ENABLE_CUDA
	Media::Decoder::H264_CUVID,
	#endif
	#ifdef ENABLE_CUDA
	Media::Decoder::H265_CUVID,
	#endif
	#ifdef ENABLE_CUDA
	Media::Decoder::MPEG2_CUVID,
	#endif
	#ifdef ENABLE_LIBVPX
	Media::Decoder::VP8_LIBVPX,
	#endif
	#ifdef ENABLE_CUDA
	Media::Decoder::VP8_CUVID,
	#endif
	#ifdef ENABLE_LIBVPX
	Media::Decoder::VP9_LIBVPX,
	#endif
	#ifdef ENABLE_CUDA
	Media::Decoder::VP9_CUVID,
	#endif
	#ifdef ENABLE_CUDA
	Media::Decoder::MPEG4_CUVID,
	#endif

	// Audio
	#ifdef ENABLE_FDK
	Media::Decoder::AAC_FRAUNHOFFER,
	#endif
	#ifdef ENABLE_LIBOPUS
	Media::Decoder::OPUS_LIBOPUS,
	#endif
	#ifdef ENABLE_LIBVORBIS
	Media::Decoder::VORBIS_LIBVORBIS,
	#endif

	// Image
};

const std::list<Media::Info::Item> Media::Info::Encoder::All = {
	// Video
	{Media::Encoder::AV1_LIBAOM,			"libaom-av1",		"AOM AV1"					},
	{Media::Encoder::AV1_RAV1E,				"librav1e",			"RAV1E AV1"					},
	{Media::Encoder::AV1_SVT,				"libsvtav1",		"SVT AV1"					},
	{Media::Encoder::AV1_NVENC,				"av1_nvenc",		"NvEnc AV1"					},
	{Media::Encoder::H264_X264,				"libx264",			"x264"						},
	{Media::Encoder::H264_OPENH264,			"libopenh264",		"OpenH264"					},
	{Media::Encoder::H264_NVENC,			"h264_nvenc",		"NvEnc H264"				},
	{Media::Encoder::H265_X265,				"libx265",			"x265"						},
	{Media::Encoder::H265_NVENC,			"hevc_nvenc",		"NvEnc H265/HEVC"			},
	{Media::Encoder::MPEG2_DEFAULT,			"mpeg2video",		"FFmpeg MPEG2"				},
	{Media::Encoder::VP8_LIBVPX,			"libvpx",			"VPX VP8"					},
	{Media::Encoder::VP9_LIBVPX,			"libvpx-vp9",		"VPX VP9"					},
	{Media::Encoder::MPEG4_DEFAULT,			"mpeg4",			"FFmpeg MPEG4(DIVX)"		},
	{Media::Encoder::MPEG4_LIBXVID,			"libxvid",			"XVID MPEG4(DIVX)"			},

	// Audio
	{Media::Encoder::AAC_DEFAULT,			"aac",				"FFmpeg AAC"				},
	{Media::Encoder::AAC_FRAUNHOFFER,		"libfdk_aac",		"Fraunhoffer AAC encoder"	},
	{Media::Encoder::AC3_DEFAULT,			"ac3",				"FFmpeg AC-3"				},
	{Media::Encoder::DTS_DEFAULT,			"dca",				"FFmpeg DTS"				},
	{Media::Encoder::EAC3_DEFAULT,			"eac3",				"FFmpeg E-AC3"				},
	{Media::Encoder::FLAC_DEFAULT,			"flac",				"FFmpeg FLACe"				},
	{Media::Encoder::MP2_DEFAULT,			"mp2",				"FFmpeg MP2"				},
	{Media::Encoder::MP2_TWOLAME,			"libtwolame",		"Twolame MP2"				},
	{Media::Encoder::MP3_LAME,				"libmp3lame",		"Lame MP3"					},
	{Media::Encoder::OPUS_DEFAULT,			"opus",				"FFmpeg OPUS"				},
	{Media::Encoder::OPUS_LIBOPUS,			"libopus",			"LibOPUS"					},
	{Media::Encoder::VORBIS_DEFAULT,		"vorbis",			"FFmpeg VORBIS"				},
	{Media::Encoder::VORBIS_LIBVORBIS,		"libvorbis",		"LibVORBIS"					},

	// Image
	{Media::Encoder::BMP_DEFAULT,			"bmp",				"FFmpeg BMP"				},
	{Media::Encoder::GIF_DEFAULT,			"gif",				"FFmpg GIF"					},
	{Media::Encoder::JPG_DEFAULT,			"mjpeg",			"FFmpeg JPG"				},
	{Media::Encoder::PNG_DEFAULT,			"png",				"FFmpeg PNG"				},
	{Media::Encoder::TIFF_DEFAULT,			"tiff",				"FFmpeg TIFF"				},
	{Media::Encoder::WEBP_LIBWEBP,			"libwebp",			"libWEBP"					}
};

const std::list<Media::Encoder::Type> Media::Info::Encoder::Available = {
	// Video
	#ifdef ENABLE_LIBAOM
	Media::Encoder::AV1_LIBAOM,
	#endif
	#ifdef ENABLE_RAV1E
	Media::Encoder::AV1_RAV1E,
	#endif
	#ifdef ENABLE_SVT_AV1
	Media::Encoder::AV1_SVT,
	#endif
	#ifdef ENABLE_NVENC
	Media::Encoder::AV1_NVENC,
	#endif
	#ifdef ENABLE_X264
	Media::Encoder::H264_X264,
	#endif
	#ifdef ENABLE_OPENH264
	Media::Encoder::H264_OPENH264,
	#endif
	#ifdef ENABLE_NVENC
	Media::Encoder::H264_NVENC,
	#endif
	#ifdef ENABLE_X265
	Media::Encoder::H265_X265,
	#endif
	#ifdef ENABLE_NVENC
	Media::Encoder::H265_NVENC,
	#endif
	Media::Encoder::MPEG2_DEFAULT,
	#ifdef ENABLE_LIBVPX
	Media::Encoder::VP8_LIBVPX,
	Media::Encoder::VP9_LIBVPX,
	#endif
	Media::Encoder::MPEG4_DEFAULT,
	#ifdef ENABLE_XVID
	Media::Encoder::MPEG4_LIBXVID,
	#endif

	// Audio
	Media::Encoder::AAC_DEFAULT,
	#ifdef ENABLE_FDK
	Media::Encoder::AAC_FRAUNHOFFER,
	#endif
	Media::Encoder::AC3_DEFAULT,
	Media::Encoder::DTS_DEFAULT,
	Media::Encoder::EAC3_DEFAULT,
	Media::Encoder::FLAC_DEFAULT,
	Media::Encoder::MP2_DEFAULT,
	#ifdef ENABLE_TWOLAME
	Media::Encoder::MP2_TWOLAME,
	#endif
	#ifdef ENABLE_LAME
	Media::Encoder::MP3_LAME,
	#endif
	Media::Encoder::OPUS_DEFAULT,
	#ifdef ENABLE_LIBOPUS
	Media::Encoder::OPUS_LIBOPUS,
	#endif
	Media::Encoder::VORBIS_DEFAULT,
	#ifdef ENABLE_LIBVORBIS
	Media::Encoder::VORBIS_LIBVORBIS,
	#endif

	// Image
	#ifdef ENABLE_IMAGE_PROCESS
	Media::Encoder::BMP_DEFAULT,
	Media::Encoder::GIF_DEFAULT,
	Media::Encoder::JPG_DEFAULT,
	Media::Encoder::PNG_DEFAULT,
	Media::Encoder::TIFF_DEFAULT,
	#ifdef ENABLE_WEBP
	Media::Encoder::WEBP_LIBWEBP
	#endif
	#endif
};