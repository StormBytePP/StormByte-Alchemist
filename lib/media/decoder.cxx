#include "decoder.hxx"

Alchemist::Media::Decoder::Base::Base(const Type& decoder_type):m_decoder_type(decoder_type) { }

Alchemist::Media::Decoder::Base::Base(Type&& decoder_type):m_decoder_type(std::move(decoder_type)) { }

Alchemist::Media::Decoder::Base::~Base() { }
