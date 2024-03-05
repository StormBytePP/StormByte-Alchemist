#include "base.hxx"
#include <utility>

STVC::Media::Codec::Base::Base(const unsigned short& codec_id): m_codec_id(codec_id) { }

STVC::Media::Codec::Base::Base(unsigned short&& codec_id): m_codec_id(std::move(codec_id)) { }

STVC::Media::Codec::Base::~Base() { }

unsigned short STVC::Media::Codec::Base::get_codec_id() const { return m_codec_id; }
