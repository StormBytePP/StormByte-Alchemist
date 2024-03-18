#include "decoder.hxx"

#ifdef ENABLE_FDK
#include "decoder/audio/aac_fraunhoffer.hxx"
#endif
#ifdef ENABLE_LIBOPUS
#include "decoder/audio/opus_libopus.hxx"
#endif
#ifdef ENABLE_LIBVORBIS
#include "decoder/audio/vorbis_libvorbis.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/av1_cuvid.hxx"
#endif
#ifdef ENABLE_DAV1D
#include "decoder/video/av1_dav1d.hxx"
#endif
#ifdef ENABLE_LIBAOM
#include "decoder/video/av1_libaom.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/h264_cuvid.hxx"
#endif
#ifdef ENABLE_OPENH264
#include "decoder/video/h264_openh264.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/h265_cuvid.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/mpeg2_cuvid.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/mpeg4_cuvid.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/vp8_cuvid.hxx"
#endif
#ifdef ENABLE_LIBVPX
#include "decoder/video/vp8_libvpx.hxx"
#endif
#ifdef ENABLE_CUDA
#include "decoder/video/vp9_cuvid.hxx"
#endif
#ifdef ENABLE_LIBVPX
#include "decoder/video/vp9_libvpx.hxx"
#endif

#include <stdexcept>

Alchemist::Media::Decoder::Base::Base(const Type& decoder_type):m_decoder_type(decoder_type) { }

Alchemist::Media::Decoder::Base::Base(Type&& decoder_type):m_decoder_type(std::move(decoder_type)) { }

Alchemist::Media::Decoder::Base::~Base() noexcept { }

Alchemist::Media::Decoder::Type Alchemist::Media::Decoder::Base::get_decoder_type() const noexcept {
	return m_decoder_type;
}

std::shared_ptr<Alchemist::Media::Decoder::Base> Alchemist::Media::Decoder::Instance(const Decoder::Type& decoder) {
	std::shared_ptr<Decoder::Base> result;

	switch(decoder) {
		case Decoder::AAC_FRAUNHOFFER:
			#ifdef ENABLE_FDK
			result.reset(new Decoder::Audio::AAC_FRAUNHOFFER());
			#else
			throw std::runtime_error("Decoder Fraunhoffer not compiled in");
			#endif
			break;

		case Decoder::OPUS_LIBOPUS:
			#ifdef ENABLE_LIBOPUS
			result.reset(new Decoder::Audio::OPUS_LIBOPUS());
			#else
			throw std::runtime_error("Decoder libopus not compiled in");
			#endif
			break;

		case Decoder::VORBIS_LIBVORBIS:
			#ifdef ENABLE_LIBVORBIS
			result.reset(new Decoder::Audio::VORBIS_LIBVORBIS());
			#else
			throw std::runtime_error("Decoder libvorbis not compiled in");
			#endif
			break;

		case Decoder::AV1_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::AV1_CUVID());
			#else
			throw std::runtime_error("Decoder AV1 CUVID not compiled in");
			#endif
			break;

		case Decoder::AV1_DAV1D:
			#ifdef ENABLE_DAV1D
			result.reset(new Decoder::Video::AV1_DAV1D());
			#else
			throw std::runtime_error("Decoder dav1d not compiled in");
			#endif
			break;

		case Decoder::AV1_LIBAOM:
			#ifdef ENABLE_LIBAOM
			result.reset(new Decoder::Video::AV1_LIBAOM());
			#else
			throw std::runtime_error("Decoder libaom not compiled in");
			#endif
			break;

		case Decoder::H264_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::H264_CUVID());
			#else
			throw std::runtime_error("Decoder H264 CUVID not compiled in");
			#endif
			break;

		case Decoder::H264_OPENH264:
			#ifdef ENABLE_OPENH264
			result.reset(new Decoder::Video::H264_OPENH264());
			#else
			throw std::runtime_error("Decoder openH264 not compiled in");
			#endif
			break;

		case Decoder::H265_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::H265_CUVID());
			#else
			throw std::runtime_error("Decoder H265 CUVID not compiled in");
			#endif
			break;

		case Decoder::MPEG2_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::MPEG2_CUVID());
			#else
			throw std::runtime_error("Decoder MPEG2 CUVID not compiled in");
			#endif
			break;

		case Decoder::MPEG4_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::MPEG4_CUVID());
			#else
			throw std::runtime_error("Decoder MPEG4 CUVID not compiled in");
			#endif
			break;

		case Decoder::VP8_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::VP8_CUVID());
			#else
			throw std::runtime_error("Decoder VP8 CUVID not compiled in");
			#endif
			break;

		case Decoder::VP8_LIBVPX:
			#ifdef ENABLE_LIBVPX
			result.reset(new Decoder::Video::VP8_LIBVPX());
			#else
			throw std::runtime_error("Decoder VP8 libvpx not compiled in");
			#endif
			break;

		case Decoder::VP9_CUVID:
			#ifdef ENABLE_CUDA
			result.reset(new Decoder::Video::VP9_CUVID());
			#else
			throw std::runtime_error("Decoder VP9 CUVID not compiled in");
			#endif
			break;

		case Decoder::VP9_LIBVPX:
			#ifdef ENABLE_LIBVPX
			result.reset(new Decoder::Video::VP9_LIBVPX());
			#else
			throw std::runtime_error("Decoder VP9 libvpx not compiled in");
			#endif
			break;
	}

	return result;
}