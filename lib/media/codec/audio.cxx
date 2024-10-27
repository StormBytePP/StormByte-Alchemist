#include "audio.hxx"

using namespace Alchemist::Media;

AudioCodec::AudioCodec(std::string&& name, std::string&& desc) noexcept:Codec(std::move(name), std::move(desc)) {}