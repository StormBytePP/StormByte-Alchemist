#include <Alchemy/media/audio/stream.hxx>

using namespace Alchemy::Media::Audio;

Stream::Stream(const int& index) noexcept:Media::Stream(index, Type::Audio) {}

void Stream::SetMetadata(const Metadata& meta) { m_metadata = std::make_shared<Metadata>(meta); }

void Stream::SetMetadata(Metadata&& meta) noexcept { m_metadata = std::make_shared<Metadata>(std::move(meta)); }