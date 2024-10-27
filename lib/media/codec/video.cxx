#include "video.hxx"

using namespace Alchemist::Media;

VideoCodec::VideoCodec(std::string&& name, std::string&& ffmpeg_name, std::string&& desc) noexcept:
Codec(std::move(name), std::move(ffmpeg_name), std::move(desc)) {}

const std::list<std::shared_ptr<Codec>> VideoCodec::All = {

};