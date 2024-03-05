#include "encoder.hxx"

const std::list<StormByte::Alchemist::Media::Encoder::Type> StormByte::Alchemist::Media::Encoder::Available {
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