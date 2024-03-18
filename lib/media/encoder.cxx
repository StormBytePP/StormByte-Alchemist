#include "encoder/copy.hxx"
#include "encoder/audio/aac_default.hxx"
#ifdef ENABLE_FDK
#include "encoder/audio/aac_fraunhoffer.hxx"
#endif
#include "encoder/audio/ac3_default.hxx"
#include "encoder/audio/dts_default.hxx"
#include "encoder/audio/eac3_default.hxx"
#include "encoder/audio/flac_default.hxx"
#include "encoder/audio/mp2_default.hxx"
#ifdef ENABLE_TWOLAME
#include "encoder/audio/mp2_twolame.hxx"
#endif
#ifdef ENABLE_LAME
#include "encoder/audio/mp3_lame.hxx"
#endif
#include "encoder/audio/opus_default.hxx"
#ifdef ENABLE_LIBOPUS
#include "encoder/audio/opus_libopus.hxx"
#endif
#include "encoder/audio/vorbis_default.hxx"
#ifdef ENABLE_LIBVORBIS
#include "encoder/audio/vorbis_libvorbis.hxx"
#endif
#include "encoder/image/bmp_default.hxx"
#include "encoder/image/gif_default.hxx"
#include "encoder/image/jpg_default.hxx"
#include "encoder/image/png_default.hxx"
#include "encoder/image/tiff_default.hxx"
#ifdef ENABLE_WEBP
#include "encoder/image/webp_libwebp.hxx"
#endif
#ifdef ENABLE_LIBAOM
#include "encoder/video/av1_libaom.hxx"
#endif
#ifdef ENABLE_NVENC
#include "encoder/video/av1_nvenc.hxx"
#endif
#ifdef ENABLE_RAV1E
#include "encoder/video/av1_rav1e.hxx"
#endif
#ifdef ENABLE_SVT_AV1
#include "encoder/video/av1_svt.hxx"
#endif
#ifdef ENABLE_NVENC
#include "encoder/video/h264_nvenc.hxx"
#endif
#ifdef ENABLE_OPENH264
#include "encoder/video/h264_openh264.hxx"
#endif
#ifdef ENABLE_X264
#include "encoder/video/h264_x264.hxx"
#endif
#ifdef ENABLE_NVENC
#include "encoder/video/h265_nvenc.hxx"
#endif
#ifdef ENABLE_X265
#include "encoder/video/h265_x265.hxx"
#endif
#include "encoder/video/mpeg2_default.hxx"
#include "encoder/video/mpeg4_default.hxx"
#ifdef ENABLE_XVID
#include "encoder/video/mpeg4_libxvid.hxx"
#endif
#ifdef ENABLE_LIBVPX
#include "encoder/video/vp8_libvpx.hxx"
#include "encoder/video/vp9_libvpx.hxx"
#endif

#include <stdexcept>

Alchemist::Media::Encoder::Base::Base(const Type& encoder_type):m_encoder_type(encoder_type) { }

Alchemist::Media::Encoder::Base::Base(Type&& encoder_type):m_encoder_type(std::move(encoder_type)) { }

Alchemist::Media::Encoder::Base::~Base() noexcept { }

Alchemist::Media::Encoder::Type Alchemist::Media::Encoder::Base::get_encoder_type() const noexcept {
	return m_encoder_type;
}

std::shared_ptr<Alchemist::Media::Encoder::Base> Alchemist::Media::Encoder::Instance(const Encoder::Type& encoder) {
	std::shared_ptr<Encoder::Base> result;

	switch(encoder) {
		case Encoder::AAC_DEFAULT:
			result.reset(new Encoder::Audio::AAC_DEFAULT());
			break;

		case Encoder::AAC_FRAUNHOFFER:
			#ifdef ENABLE_FDK
			result.reset(new Encoder::Audio::AAC_FRAUNHOFFER());
			#else
			throw std::runtime_error("Encoder Fraunhoffer not compiled in");
			#endif
			break;

		case Encoder::AC3_DEFAULT:
			result.reset(new Encoder::Audio::AC3_DEFAULT());
			break;

		case Encoder::DTS_DEFAULT:
			result.reset(new Encoder::Audio::DTS_DEFAULT());
			break;

		case Encoder::EAC3_DEFAULT:
			result.reset(new Encoder::Audio::EAC3_DEFAULT());
			break;

		case Encoder::FLAC_DEFAULT:
			result.reset(new Encoder::Audio::FLAC_DEFAULT());
			break;

		case Encoder::MP2_DEFAULT:
			result.reset(new Encoder::Audio::MP2_DEFAULT());
			break;

		case Encoder::MP2_TWOLAME:
			#ifdef ENABLE_TWOLAME
			result.reset(new Encoder::Audio::MP2_TWOLAME());
			#else
			throw std::runtime_error("Encoder twolame not compiled in");
			#endif
			break;

		case Encoder::MP3_LAME:
			#ifdef ENABLE_LAME
			result.reset(new Encoder::Audio::MP3_LAME());
			#else
			throw std::runtime_error("Encoder lame not compiled in");
			#endif
			break;

		case Encoder::OPUS_DEFAULT:
			result.reset(new Encoder::Audio::OPUS_DEFAULT());
			break;

		case Encoder::OPUS_LIBOPUS:
			#ifdef ENABLE_LIBOPUS
			result.reset(new Encoder::Audio::OPUS_LIBOPUS());
			#else
			throw std::runtime_error("Encoder libopus not compiled in");
			#endif
			break;

		case Encoder::VORBIS_DEFAULT:
			result.reset(new Encoder::Audio::VORBIS_DEFAULT());
			break;

		case Encoder::VORBIS_LIBVORBIS:
			#ifdef ENABLE_LIBVORBIS
			result.reset(new Encoder::Audio::VORBIS_LIBVORBIS());
			#else
			throw std::runtime_error("Encoder libvorbis not compiled in");
			#endif
			break;

		case Encoder::BMP_DEFAULT:
			result.reset(new Encoder::Image::BMP_DEFAULT());
			break;

		case Encoder::GIF_DEFAULT:
			result.reset(new Encoder::Image::GIF_DEFAULT());
			break;

		case Encoder::JPG_DEFAULT:
			result.reset(new Encoder::Image::JPG_DEFAULT());
			break;

		case Encoder::PNG_DEFAULT:
			result.reset(new Encoder::Image::PNG_DEFAULT());
			break;

		case Encoder::TIFF_DEFAULT:
			result.reset(new Encoder::Image::TIFF_DEFAULT());
			break;

		case Encoder::WEBP_LIBWEBP:
			#ifdef ENABLE_WEBP
			result.reset(new Encoder::Image::WEBP_LIBWEBP());
			#else
			throw std::runtime_error("Encoder libwebp not compiled in");
			#endif
			break;

		case Encoder::AV1_LIBAOM:
			#ifdef ENABLE_LIBAOM
			result.reset(new Encoder::Video::AV1_LIBAOM());
			#else
			throw std::runtime_error("Encoder libaom not compiled in");
			#endif
			break;

		case Encoder::AV1_NVENC:
			#ifdef ENABLE_NVENC
			result.reset(new Encoder::Video::AV1_NVENC());
			#else
			throw std::runtime_error("Encoder AV1 NVenc not compiled in");
			#endif
			break;

		case Encoder::AV1_RAV1E:
			#ifdef ENABLE_RAV1E
			result.reset(new Encoder::Video::AV1_RAV1E());
			#else
			throw std::runtime_error("Encoder RAV1E not compiled in");
			#endif
			break;

		case Encoder::AV1_SVT:
			#ifdef ENABLE_SVT_AV1
			result.reset(new Encoder::Video::AV1_SVT());
			#else
			throw std::runtime_error("Encoder SVT not compiled in");
			#endif
			break;

		case Encoder::H264_NVENC:
			#ifdef ENABLE_NVENC
			result.reset(new Encoder::Video::H264_NVENC());
			#else
			throw std::runtime_error("Encoder H264 NVEnc not compiled in");
			#endif
			break;

		case Encoder::H264_OPENH264:
			#ifdef ENABLE_OPENH264
			result.reset(new Encoder::Video::H264_OPENH264());
			#else
			throw std::runtime_error("Encoder openH264 not compiled in");
			#endif
			break;

		case Encoder::H264_X264:
			#ifdef ENABLE_X264
			result.reset(new Encoder::Video::H264_X264());
			#else
			throw std::runtime_error("Encoder x264 not compiled in");
			#endif
			break;

		case Encoder::H265_NVENC:
			#ifdef ENABLE_NVENC
			result.reset(new Encoder::Video::H265_NVENC());
			#else
			throw std::runtime_error("Encoder H265 NVEnc not compiled in");
			#endif
			break;

		case Encoder::H265_X265:
			#ifdef ENABLE_X265
			result.reset(new Encoder::Video::H265_X265());
			#else
			throw std::runtime_error("Encoder x265 not compiled in");
			#endif
			break;

		case Encoder::MPEG2_DEFAULT:
			result.reset(new Encoder::Video::MPEG2_DEFAULT());
			break;

		case Encoder::MPEG4_DEFAULT:
			result.reset(new Encoder::Video::MPEG4_DEFAULT());
			break;

		case Encoder::MPEG4_LIBXVID:
			#ifdef ENABLE_XVID
			result.reset(new Encoder::Video::MPEG4_LIBXVID());
			#else
			throw std::runtime_error("Encoder XVID not compiled in");
			#endif
			break;

		case Encoder::VP8_LIBVPX:
			#ifdef ENABLE_LIBVPX
			result.reset(new Encoder::Video::VP8_LIBVPX());
			#else
			throw std::runtime_error("Encoder libVPX not compiled in");
			#endif
			break;

		case Encoder::VP9_LIBVPX:
			#ifdef ENABLE_LIBVPX
			result.reset(new Encoder::Video::VP9_LIBVPX());
			#else
			throw std::runtime_error("Encoder libVPX not compiled in");
			#endif
			break;

		case Encoder::COPY:
			result.reset(new Encoder::Copy());
	}

	return result;
}
