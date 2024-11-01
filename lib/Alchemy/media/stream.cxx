#include <Alchemy/media/stream.hxx>

using namespace Alchemist::Media;

Stream::Stream(const unsigned short& index, const Type& type) noexcept:m_index(index), m_type(type) {}

Stream::~Stream() noexcept {}

const unsigned short& Stream::GetIndex() const noexcept { return m_index; }

const Type& Stream::GetType() const noexcept { return m_type; }

void Stream::SetIndex(const unsigned short& index) noexcept { m_index = index; }

const std::optional<std::string>& Stream::GetLanguage() const noexcept { return m_language; }

void Stream::SetLanguage(const std::string& language) { m_language = language; }

const std::optional<std::string>& Stream::GetTitle() const noexcept { return m_title; }

void Stream::SetTitle(const std::string& title) { m_title = title; }

bool Stream::IsDefault() const noexcept { return m_default; }

void Stream::SetDefaultStatus(bool def) { m_default = def; }

bool Stream::IsForced() const noexcept { return m_forced; }

void Stream::SetForcedStatus(bool forced) { m_forced = forced; }

const std::shared_ptr<Codec>& Stream::GetCodec() const noexcept { return m_codec; }

void Stream::SetCodec(std::shared_ptr<Codec> codec) noexcept { m_codec = codec; }

const std::shared_ptr<Metadata>& Stream::GetMetadata() const noexcept { return m_metadata; }