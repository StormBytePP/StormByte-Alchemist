#include "codec/audio/aac.hxx"
#include "codec/audio/ac3.hxx"
#include "codec/audio/copy.hxx"
#include "codec/audio/dts.hxx"
#include "codec/audio/eac3.hxx"
#include "codec/audio/flac.hxx"
#include "codec/audio/mp2.hxx"
#include "codec/audio/mp3.hxx"
#include "codec/audio/opus.hxx"
#include "codec/audio/vorbis.hxx"
#include "codec/image/bmp.hxx"
#include "codec/image/copy.hxx"
#include "codec/image/gif.hxx"
#include "codec/image/jpg.hxx"
#include "codec/image/png.hxx"
#include "codec/image/tiff.hxx"
#include "codec/image/webp.hxx"
#include "codec/video/av1.hxx"
#include "codec/video/copy.hxx"
#include "codec/video/h264.hxx"
#include "codec/video/h265.hxx"
#include "codec/video/mpeg2.hxx"
#include "codec/video/mpeg4.hxx"
#include "codec/video/vp8.hxx"
#include "codec/video/vp9.hxx"
#include "media/info.hxx"

#include <algorithm>

Alchemist::Media::Codec::Base::Base(const Codec::Type& codec_type):Item(), m_codec_type(codec_type) { }

Alchemist::Media::Codec::Base::Base(Codec::Type&& codec_type):Item(), m_codec_type(std::move(codec_type)) { }

Alchemist::Media::Codec::Type Alchemist::Media::Codec::Base::get_codec_type() const noexcept {
	return m_codec_type;
}

const std::optional<std::string>& Alchemist::Media::Codec::Base::get_language() const noexcept { return m_language; }

void Alchemist::Media::Codec::Base::set_language(const std::string& lang) { m_language = lang; }

void Alchemist::Media::Codec::Base::set_language(std::string&& lang) noexcept { m_language.emplace(std::move(lang)); }

std::shared_ptr<Alchemist::Media::Codec::Base> Alchemist::Media::Codec::Instance(const Codec::Type& codec) {
	std::shared_ptr<Codec::Base> result;
	
	switch(codec) {
		case Codec::AAC:
			result.reset(new Codec::Audio::AAC());
			break;

		case Codec::AC3:
			result.reset(new Codec::Audio::AC3());
			break;

		case Codec::DTS:
			result.reset(new Codec::Audio::DTS());
			break;

		case Codec::EAC3:
			result.reset(new Codec::Audio::EAC3());
			break;

		case Codec::FLAC:
			result.reset(new Codec::Audio::FLAC());
			break;

		case Codec::MP2:
			result.reset(new Codec::Audio::MP2());
			break;

		case Codec::MP3:
			result.reset(new Codec::Audio::MP3());
			break;

		case Codec::OPUS:
			result.reset(new Codec::Audio::OPUS());
			break;

		case Codec::VORBIS:
			result.reset(new Codec::Audio::VORBIS());
			break;

		case Codec::COPY_AUDIO:
			result.reset(new Codec::Audio::Copy());
			break;

		case Codec::BMP:
			result.reset(new Codec::Image::BMP());
			break;

		case Codec::GIF:
			result.reset(new Codec::Image::GIF());
			break;

		case Codec::JPG:
			result.reset(new Codec::Image::JPG());
			break;

		case Codec::PNG:
			result.reset(new Codec::Image::PNG());
			break;

		case Codec::TIFF:
			result.reset(new Codec::Image::TIFF());
			break;

		case Codec::WEBP:
			result.reset(new Codec::Image::WEBP());
			break;

		case Codec::COPY_IMAGE:
			result.reset(new Codec::Image::Copy());
			break;

		case Codec::AV1:
			result.reset(new Codec::Video::AV1());
			break;

		case Codec::H264:
			result.reset(new Codec::Video::H264());
			break;

		case Codec::H265:
			result.reset(new Codec::Video::H265());
			break;

		case Codec::MPEG2:
			result.reset(new Codec::Video::MPEG2());
			break;

		case Codec::MPEG4:
			result.reset(new Codec::Video::MPEG4());
			break;

		case Codec::VP8:
			result.reset(new Codec::Video::VP8());
			break;

		case Codec::VP9:
			result.reset(new Codec::Video::VP9());
			break;

		case Codec::COPY_VIDEO:
			result.reset(new Codec::Video::Copy());
			break;
	}

	return result;
}

std::shared_ptr<Alchemist::Media::Codec::Base> Alchemist::Media::Codec::Instance(const std::string& codec) {
	std::shared_ptr<Base> result;

	const auto& all_codecs = Info::Codec::All;

	const auto iterator = std::find_if(
		all_codecs.begin(),
		all_codecs.end(),
		[&](const Alchemist::Media::Info::Item& item) { return item.short_name == codec; }
	);

	if (iterator != all_codecs.end())
		result = Codec::Instance(static_cast<Codec::Type>(iterator->id));

	return result;
}