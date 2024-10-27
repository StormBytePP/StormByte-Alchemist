#include "video.hxx"

using namespace Alchemist::Media;

VideoCodec::VideoCodec(std::string&& name, std::string&& desc) noexcept:Codec(std::move(name), std::move(desc)) {}