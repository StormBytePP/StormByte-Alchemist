#include "stream.hxx"

using namespace Alchemist::Media::Video;

Stream::Stream(const unsigned short& index) noexcept:Media::Stream(index, 'v') {}

void Stream::SetMetadata(const Metadata& meta) { m_metadata = std::make_shared<Metadata>(meta); }

void Stream::SetMetadata(Metadata&& meta) noexcept { m_metadata = std::make_shared<Metadata>(std::move(meta)); }