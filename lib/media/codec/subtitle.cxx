#include "subtitle.hxx"

using namespace Alchemist::Media;

SubtitleCodec::SubtitleCodec(std::string&& name, std::string&& desc) noexcept:Codec(std::move(name), std::move(desc)) {}