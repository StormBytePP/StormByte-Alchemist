#include <Alchemy/media/video/stream.hxx>

using namespace Alchemy::Media::Video;

Stream::Stream(const int& index) noexcept:Media::Stream(index, Type::Video) {}

void Stream::SetMetadata(const Metadata& meta) { m_metadata = std::make_shared<Metadata>(meta); }

void Stream::SetMetadata(Metadata&& meta) noexcept { m_metadata = std::make_shared<Metadata>(std::move(meta)); }