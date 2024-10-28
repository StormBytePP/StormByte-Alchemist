#include "codec.hxx"

using namespace Alchemist::Media;

Codec::Codec(std::string&& name, std::string&& ffmpeg_name, std::string&& desc) noexcept:
m_name(std::move(name)), m_ffmpeg_name(ffmpeg_name), m_description(std::move(desc)), m_supported(true) {}

Codec::~Codec() noexcept {}

const std::string& Codec::GetName() const noexcept { return m_name; }

const std::string& Codec::GetFFmpegName() const noexcept { return m_ffmpeg_name; }

const std::string& Codec::GetDescription() const noexcept { return m_description; }

bool Codec::IsSupported() const noexcept { return m_supported; }