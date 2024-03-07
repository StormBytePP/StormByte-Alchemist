#include "codec.hxx"

Alchemist::Media::Codec::Base::Base(const Codec::Type& codec_type):m_codec_type(codec_type) { }

Alchemist::Media::Codec::Base::Base(Codec::Type&& codec_type):m_codec_type(std::move(codec_type)) { }

Alchemist::Media::Codec::Type Alchemist::Media::Codec::Base::get_codec_type() const {
	return m_codec_type;
}
