#include "h264.hxx"

Alchemist::Media::Codec::Video::H264::H264():Base(Codec::H264) { }

std::list<Alchemist::Media::Decoder::Type> Alchemist::Media::Codec::Video::H264::get_available_decoders() const {
	return {
		#ifdef ENABLE_CUDA
		Decoder::H264_CUVID,
		#endif
		#ifdef ENABLE_OPENH264
		Decoder::H264_OPENH264,
		#endif
	};
}

std::list<Alchemist::Media::Encoder::Type> Alchemist::Media::Codec::Video::H264::get_available_encoders() const {
	return {
		#ifdef ENABLE_NVENC
		Encoder::H264_NVENC,
		#endif
		#ifdef ENABLE_OPENH264
		Encoder::H264_OPENH264,
		#endif
		#ifdef ENABLE_X264
		Encoder::H264_X264,
		#endif
	};
}