#include "stream.hxx"

using namespace Alchemist::Media::Video;

void Stream::SetMetadata(const Metadata& meta) { m_metadata = std::make_shared<Metadata>(meta); }

void Stream::SetMetadata(Metadata&& meta) noexcept { m_metadata = std::make_shared<Metadata>(std::move(meta)); }