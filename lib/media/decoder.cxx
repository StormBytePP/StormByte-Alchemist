#include "decoder.hxx"

const std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Decoder::Available() {
	return {
		// Video
		AV1_DEFAULT,
		#ifdef ENABLE_DAV1D
		AV1_DAV1D,
		#endif
		#ifdef ENABLE_LIBAOM
		AV1_AOM,
		#endif
		#ifdef ENABLE_CUDA
		AV1_CUVID,
		#endif
		H264_DEFAULT,
		#ifdef ENABLE_OPENH264
		H264_OPENH264,
		#endif
		#ifdef ENABLE_CUDA
		H264_CUVID,
		#endif
		H265_DEFAULT,
		#ifdef ENABLE_CUDA
		H265_CUVID,
		#endif
		MPEG2_DEFAULT,
		#ifdef ENABLE_CUDA
		MPEG2_CUVID,
		#endif
		VP8_DEFAULT,
		#ifdef ENABLE_LIBVPX
		VP8_LIBVPX,
		#endif
		#ifdef ENABLE_CUDA
		VP8_CUVID,
		#endif
		VP9_DEFAULT,
		#ifdef ENABLE_LIBVPX
		VP9_LIBVPX,
		#endif
		#ifdef ENABLE_CUDA
		VP9_CUVID,
		#endif
		MPEG4_DEFAULT,
		#ifdef ENABL_CUDA
		MPEG4_CUVID,
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
		MP3_DEFAULT,
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
		WEBP_DEFAULT
	};
}

const std::map<Alchemist::Media::Decoder::Type, Alchemist::Media::Info> DLL_PUBLIC Alchemist::Media::Decoder::Metadata() {
	return {
		// Video
		{AV1_DEFAULT,		{"av1",				"FFmpeg AV1"}},
		{AV1_DAV1D,			{"libdav1d",		"DAV1D"}},
		{AV1_AOM,			{"libaom-av1",		"AOM AV1"}},
		{AV1_CUVID,			{"av1_cuvid",		"CuVid AV1"}},
		{H264_DEFAULT,		{"h264",			"FFmpeg H264"}},
		{H264_OPENH264,		{"libopenh264",		"OpenH264"}},
		{H264_CUVID,		{"h264_cuvid",		"CuVid H264"}},
		{H265_DEFAULT,		{"hevc",			"FFmpeg H265(HEVC)"}},
		{H265_CUVID,		{"hevc_cuvid",		"CuVid H265(HEVC)"}},
		{MPEG2_DEFAULT,		{"mpeg2video",		"FFmpeg MPEG-2"}},
		{MPEG2_CUVID,		{"mpeg2_cuvid",		"CuVid MPEG-2"}},
		{VP8_DEFAULT,		{"vp8",				"FFmpeg VP8"}},
		{VP8_LIBVPX,		{"libvpx",			"VPX VP8"}},
		{VP8_CUVID,			{"vp8_cuvid",		"CuVid VP8"}},
		{VP9_DEFAULT,		{"vp9",				"FFmpeg VP9"}},
		{VP9_LIBVPX,		{"libvpx-vp9",		"VPX VP9"}},
		{VP9_CUVID,			{"vp9_cuvid",		"CuVid VP9"}},
		{MPEG4_DEFAULT,		{"mpeg4",			"FFmpeg MPEG-4"}},
		{MPEG4_CUVID,		{"mpeg4_cuvid",		"CuVid MPEG-4"}},

		// Audio
		{AAC_DEFAULT,		{"aac",				"FFmpeg AAC"}},
		{AAC_FRAUNHOFFER,	{"libfdk_aac",		"Fraunhoffer AAC"}},
		{AC3_DEFAULT,		{"ac3",				"FFmpeg AC3"}},
		{DTS_DEFAULT,		{"dca",				"FFmpeg DTS"}},
		{EAC3_DEFAULT,		{"eac3",			"FFmpeg EAC3"}},
		{FLAC_DEFAULT,		{"flac",			"FFmpeg FLAC"}},
		{MP2_DEFAULT,		{"mp2",				"FFmpeg MP2"}},
		{MP3_DEFAULT,		{"mp3",				"FFmpeg mp3"}},
		{OPUS_DEFAULT,		{"opus",			"FFmpeg OPUS"}},
		{OPUS_LIBOPUS,		{"libopus",			"LibOpus"}},
		{VORBIS_DEFAULT,	{"vorbis",			"FFmpeg VORBIS"}},
		{VORBIS_LIBVORBIS,	{"libvorbis",		"LibVorbis"}},

		// Image
		{BMP_DEFAULT,		{"bmp",				"FFmpeg BMP"}},
		{GIF_DEFAULT,		{"gif",				"FFmpeg GIF"}},
		{JPG_DEFAULT,		{"mjpeg",			"FFmpeg JPG"}},
		{PNG_DEFAULT,		{"png",				"FFmpeg PNG"}},
		{TIFF_DEFAULT,		{"tiff",			"FFmpeg TIFF"}},
		{WEBP_DEFAULT,		{"webp",			"FFmpeg WEBP"}}
	};
}

Alchemist::Media::Decoder::Base::Base(const Type& decoder_type):m_decoder_type(decoder_type) { }

Alchemist::Media::Decoder::Base::Base(Type&& decoder_type):m_decoder_type(std::move(decoder_type)) { }

Alchemist::Media::Decoder::Base::~Base() { }