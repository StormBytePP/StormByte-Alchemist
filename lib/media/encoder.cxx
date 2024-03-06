#include "encoder.hxx"

const std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Encoder::Available() {
	return {
		// Video
		#ifdef ENABLE_LIBAOM
		AV1_AOM,
		#endif
		#ifdef ENABLE_RAV1E
		AV1_RAV1E,
		#endif
		#ifdef ENABLE_SVT_AV1
		AV1_SVT,
		#endif
		#ifdef ENABLE_NVENC
		AV1_NVENC,
		#endif
		#ifdef ENABLE_X264
		H264_X264,
		#endif
		#ifdef ENABLE_OPENH264
		H264_OPENH264,
		#endif
		#ifdef ENABLE_NVENC
		H264_NVENC,
		#endif
		#ifdef ENABLE_X265
		H265_X265,
		#endif
		#ifdef ENABLE_NVENC
		H265_NVENC,
		#endif
		MPEG2_VIDEO,
		#ifdef ENABLE_LIBVPX
		VP8_LIBVPX,
		VP9_LIBVPX,
		#endif
		MPEG4_DEFAULT,
		#ifdef ENABLE_XVID
		MPEG4_LIBXVID,
		#endif

		// Audio
		AAC_DEFAULT,
		#ifdef ENABLE_FDK
		AAC_FRAUNHOFFER,
		#endif
		AC3_DEFAULT,
		DTS_DEFAULT,
		EAC3_DEFAULT,
		FLAC_DEFAULT,
		MP2_DEFAULT,
		#ifdef ENABLE_TWOLAME
		MP2_TWOLAME,
		#endif
		#ifdef ENABLE_LAME
		MP3_LAME,
		#endif
		OPUS_DEFAULT,
		#ifdef ENABLE_LIBOPUS
		OPUS_LIBOPUS,
		#endif
		VORBIS_DEFAULT,
		#ifdef ENABLE_LIBVORBIS
		VORBIS_LIBVORBIS,
		#endif

		// Image
		BMP_DEFAULT,
		GIF_DEFAULT,
		JPG_DEFAULT,
		PNG_DEFAULT,
		TIFF_DEFAULT,
		#ifdef ENABLE_WEBP
		WEBP_LIBWEBP
		#endif
	};
}

const std::map<Alchemist::Media::Encoder::Type, Alchemist::Media::Info> DLL_PUBLIC Alchemist::Media::Encoder::Metadata() {
	return {
		// Video
		{AV1_AOM,				{"libaom-av1",		"AOM AV1"}},
		{AV1_RAV1E,				{"librav1e",		"RAV1E AV1"}},
		{AV1_SVT,				{"libsvtav1",		"SVT AV1"}},
		{AV1_NVENC,				{"av1_nvenc",		"NvEnc AV1"}},
		{H264_X264,				{"libx264",			"x264"}},
		{H264_OPENH264,			{"libopenh264",		"OpenH264"}},
		{H264_NVENC,			{"h264_nvenc",		"NvEnc H264"}},
		{H265_X265,				{"libx265",			"x265"}},
		{H265_NVENC,			{"hevc_nvenc",		"NvEnc H265/HEVC"}},
		{MPEG2_VIDEO,			{"mpeg2video",		"FFmpeg MPEG2"}},
		{VP8_LIBVPX,			{"libvpx",			"VPX VP8"}},
		{VP9_LIBVPX,			{"libvpx-vp9",		"VPX VP9"}},
		{MPEG4_DEFAULT,			{"mpeg4",			"FFmpeg MPEG4(DIVX)"}},
		{MPEG4_LIBXVID,			{"libxvid",			"XVID MPEG4(DIVX)e"}},

		// Audio
		{AAC_DEFAULT,			{"aac",				"FFmpeg AAC"}},
		{AAC_FRAUNHOFFER,		{"libfdk_aac",		"Fraunhoffer AAC encodeer"}},
		{AC3_DEFAULT,			{"ac3",				"FFmpeg AC-3"}},
		{DTS_DEFAULT,			{"dca",				"FFmpeg DTS"}},
		{EAC3_DEFAULT,			{"eac3",			"FFmpeg E-AC3"}},
		{FLAC_DEFAULT,			{"flac",			"FFmpeg FLACe"}},
		{MP2_DEFAULT,			{"mp2",				"FFmpeg MP2"}},
		{MP2_TWOLAME,			{"libtwolame",		"Twolame MP2"}},
		{MP3_LAME,				{"libmp3lame",		"Lame MP3"}},
		{OPUS_DEFAULT,			{"opus",			"FFmpeg OPUS"}},
		{OPUS_LIBOPUS,			{"libopus",			"LibOPUS"}},
		{VORBIS_DEFAULT,		{"vorbis",			"FFmpeg VORBIS"}},
		{VORBIS_LIBVORBIS,		{"libvorbis",		"LibVORBIS"}},

		// Image
		{BMP_DEFAULT,			{"bmp",				"FFmpeg BMP"}},
		{GIF_DEFAULT,			{"gif",				"FFmpg GIF"}},
		{JPG_DEFAULT,			{"mjpeg",			"FFmpeg JPG"}},
		{PNG_DEFAULT,			{"png",				"FFmpeg PNG"}},
		{TIFF_DEFAULT,			{"tiff",			"FFmpeg TIFF"}},
		{WEBP_LIBWEBP,			{"libwebp",			"libWEBP"}}
	};
}