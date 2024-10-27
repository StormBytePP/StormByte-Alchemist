#include "subtitle.hxx"

using namespace Alchemist::Media;

SubtitleCodec::SubtitleCodec(std::string&& name, std::string&& ffmpeg_name, std::string&& desc) noexcept:
Codec(std::move(name), std::move(ffmpeg_name), std::move(desc)) {}

const std::list<std::shared_ptr<Codec>> SubtitleCodec::All = {

};