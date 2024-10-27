#include "audio.hxx"

using namespace Alchemist::Media;

AudioCodec::AudioCodec(std::string&& name, std::string&& ffmpeg_name, std::string&& desc) noexcept:
Codec(std::move(name), std::move(ffmpeg_name), std::move(desc)) {}

const std::list<std::shared_ptr<Codec>> AudioCodec::All = {

};