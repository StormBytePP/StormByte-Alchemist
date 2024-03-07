#include "encoder.hxx"

Alchemist::Media::Encoder::Base::Base(const Type& encoder_type):m_encoder_type(encoder_type) { }

Alchemist::Media::Encoder::Base::Base(Type&& encoder_type):m_encoder_type(std::move(encoder_type)) { }

Alchemist::Media::Encoder::Base::~Base() { }
