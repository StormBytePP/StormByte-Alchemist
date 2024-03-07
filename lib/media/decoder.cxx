#include "decoder/audio/aac_default.hxx"
#ifdef ENABLE_FDK
#include "decoder/audio/aac_fraunhoffer.hxx"
#endif
#include "decoder/audio/ac3_default.hxx"
#include "decoder/audio/dts_default.hxx"
#include "decoder/audio/eac3_default.hxx"
#include "decoder/audio/flac_default.hxx"
#include "decoder/audio/mp2_default.hxx"
#include "decoder/audio/mp3_default.hxx"
#include "decoder/audio/opus_default.hxx"
#ifdef ENABLE_LIBOPUS
#include "decoder/audio/opus_libopus.hxx"
#endif
#include "decoder/audio/vorbis_default.hxx"
#ifdef ENABLE_LIBVORBIS
#include "decoder/audio/vorbis_libvorbis.hxx"
#endif
#include "decoder/image/bmp_default.hxx"
#include "decoder/image/gif_default.hxx"
#include "decoder/image/jpg_default.hxx"
#include "decoder/image/png_default.hxx"
#include "decoder/image/tiff_default.hxx"
#include "decoder/image/webp_default.hxx"
#ifdef ENABLE_CUDA
#include "decoder/video/av1_cuvid.hxx"
#endif
#ifdef ENABLE_DAV1D
#include "decoder/video/av1_dav1d.hxx"
#endif
#include "decoder/video/av1_default.hxx"
#ifdef ENABLE_LIBAOM
#include "decoder/video/av1_libaom.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/h264_cuvid.hxx"
#endif
#include "decoder/video/h264_default.hxx"
#ifdef ENABLE_OPENH264
#include "decoder/video/h264_openh264.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/h265_cuvid.hxx"
#endif
#include "decoder/video/h265_default.hxx"
#ifdef ENABLE_CUDA
#include "decoder/video/mpeg2_cuvid.hxx"
#endif
#include "decoder/video/mpeg2_default.hxx"
#ifdef ENABLE_CUDA
#include "decoder/video/mpeg4_cuvid.hxx"
#endif
#include "decoder/video/mpeg4_default.hxx"
#ifdef ENABLE_CUDA
#include "decoder/video/vp8_cuvid.hxx"
#endif
#include "decoder/video/vp8_default.hxx"
#ifdef ENABLE_LIBVPX
#include "decoder/video/vp8_libvpx.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/vp9_cuvid.hxx"
#endif
#include "decoder/video/vp9_default.hxx"
#ifdef ENABLE_LIBVPX
#include "decoder/video/vp9_libvpx.hxx"
#endif

#include <exception>

Alchemist::Media::Decoder::Base::Base(const Type& decoder_type):m_decoder_type(decoder_type) { }

Alchemist::Media::Decoder::Base::Base(Type&& decoder_type):m_decoder_type(std::move(decoder_type)) { }

Alchemist::Media::Decoder::Base::~Base() { }

std::shared_ptr<Alchemist::Media::Decoder::Base> Alchemist::Media::Decoder::Instance(const Decoder::Type& decoder) {
	std::shared_ptr<Decoder::Base> result;

	switch(decoder) {
		case Decoder::AAC_DEFAULT:
			result.reset(new Decoder::Audio::AAC_DEFAULT());
			break;

		case Decoder::AAC_FRAUNHOFFER:
			result.reset(new Decoder::Audio::AAC_FRAUNHOFFER());
			break;

		case Decoder::AC3_DEFAULT:
			result.reset(new Decoder::Audio::AC3_DEFAULT());
			break;

		case Decoder::DTS_DEFAULT:
			result.reset(new Decoder::Audio::DTS_DEFAULT());
			break;

		case Decoder::EAC3_DEFAULT:
			result.reset(new Decoder::Audio::EAC3_DEFAULT());
			break;

		case Decoder::FLAC_DEFAULT:
			result.reset(new Decoder::Audio::FLAC_DEFAULT());
			break;

		case Decoder::MP2_DEFAULT:
			result.reset(new Decoder::Audio::MP2_DEFAULT());
			break;

		case Decoder::MP3_DEFAULT:
			result.reset(new Decoder::Audio::MP3_DEFAULT());
			break;

		case Decoder::OPUS_DEFAULT:
			result.reset(new Decoder::Audio::OPUS_DEFAULT());
			break;

		case Decoder::OPUS_LIBOPUS:
			#ifdef ENABLE_LIBOPUS
			result.reset(new Decoder::Audio::OPUS_LIBOPUS());
			#else
			throw std::runtime_exception("Decoder libopus not compiled in");
			#endif
			break;

		case Decoder::VORBIS_DEFAULT:
			result.reset(new Decoder::Audio::VORBIS_DEFAULT());
			break;

		case Decoder::VORBIS_LIBVORBIS:
			#ifdef ENABLE_LIBVORBIS
			result.reset(new Decoder::Audio::VORBIS_LIBVORBIS());
			#else
			throw std::runtime_exception("Decoder libvorbis not compiled in");
			#endif
			break;

		case Decoder::BMP_DEFAULT:
			result.reset(new Decoder::Image::BMP_DEFAULT());
			break;

		case Decoder::GIF_DEFAULT:
			result.reset(new Decoder::Image::GIF_DEFAULT());
			break;

		case Decoder::JPG_DEFAULT:
			result.reset(new Decoder::Image::JPG_DEFAULT());
			break;

		case Decoder::PNG_DEFAULT:
			result.reset(new Decoder::Image::PNG_DEFAULT());
			break;

		case Decoder::TIFF_DEFAULT:
			result.reset(new Decoder::Image::TIFF_DEFAULT());
			break;

		case Decoder::WEBP_DEFAULT:
			result.reset(new Decoder::Image::WEBP_DEFAULT());
			break;

		case Decoder::AV1_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::AV1_CUVID());
			#else
			throw std::runtime_exception("Decoder AV1 CUVID not compiled in");
			#endif
			break;

		case Decoder::AV1_DAV1D:
			#ifdef ENABLE_DAV1D
			result.reset(new Decoder::Video::AV1_DAV1D());
			#else
			throw std::runtime_exception("Decoder dav1d not compiled in");
			#endif
			break;

		case Decoder::AV1_DEFAULT:
			result.reset(new Decoder::Video::AV1_DEFAULT());
			break;

		case Decoder::AV1_LIBAOM:
			#ifdef ENABLE_LIBAOM
			result.reset(new Decoder::Video::AV1_LIBAOM());
			#else
			throw std::runtime_exception("Decoder libaom not compiled in");
			#endif
			break;

		case Decoder::H264_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::H264_CUVID());
			#else
			throw std::runtime_exception("Decoder H264 CUVID not compiled in");
			#endif
			break;

		case Decoder::H264_DEFAULT:
			result.reset(new Decoder::Video::H264_DEFAULT());
			break;

		case Decoder::H264_OPENH264:
			#ifdef ENABLE_OPENH264
			result.reset(new Decoder::Video::H264_OPENH264());
			#else
			throw std::runtime_exception("Decoder openH264 not compiled in");
			#endif
			break;

		case Decoder::H265_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::H265_CUVID());
			#else
			throw std::runtime_exception("Decoder H265 CUVID not compiled in");
			#endif
			break;

		case Decoder::H265_DEFAULT:
			result.reset(new Decoder::Video::H265_DEFAULT());
			break;

		case Decoder::MPEG2_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::MPEG2_CUVID());
			#else
			throw std::runtime_exception("Decoder MPEG2 CUVID not compiled in");
			#endif
			break;

		case Decoder::MPEG2_DEFAULT:
			result.reset(new Decoder::Video::MPEG2_DEFAULT());
			break;

		case Decoder::MPEG4_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::MPEG4_CUVID());
			#else
			throw std::runtime_exception("Decoder MPEG4 CUVID not compiled in");
			#endif
			break;

		case Decoder::MPEG4_DEFAULT:
			result.reset(new Decoder::Video::MPEG4_DEFAULT());
			break;

		case Decoder::VP8_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::VP8_CUVID());
			#else
			throw std::runtime_exception("Decoder VP8 CUVID not compiled in");
			#endif
			break;

		case Decoder::VP8_DEFAULT:
			result.reset(new Decoder::Video::VP8_DEFAULT());
			break;

		case Decoder::VP8_LIBVPX:
			#ifdef ENABLE_LIBVPX
			result.reset(new Decoder::Video::VP8_LIBVPX());
			#else
			throw std::runtime_exception("Decoder VP8 libvpx not compiled in");
			#endif
			break;

		case Decoder::VP9_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::VP9_CUVID());
			#else
			throw std::runtime_exception("Decoder VP9 CUVID not compiled in");
			#endif
			break;

		case Decoder::VP9_DEFAULT:
			result.reset(new Decoder::Video::VP9_DEFAULT());
			break;

		case Decoder::VP9_LIBVPX:
			#ifdef ENABLE_LIBVPX
			result.reset(new Decoder::Video::VP9_LIBVPX());
			#else
			throw std::runtime_exception("Decoder VP9 libvpx not compiled in");
			#endif
			break;
	}

	return result;
}