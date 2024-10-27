#include "stream.hxx"

using namespace Alchemist::Media;

Stream::Stream(std::shared_ptr<Codec> codec):m_default(false), m_forced(false), m_codec(codec) {}

Stream::~Stream() {}

const std::optional<std::string>& Stream::GetLanguage() const { return m_language; }

void Stream::SetLanguage(const std::string& language) { m_language = language; }

const std::optional<std::string>& Stream::GetTitle() const { return m_title; }

void Stream::SetTitle(const std::string& title) { m_title = title; }

bool Stream::IsDefault() const { return m_default; }

void Stream::SetDefaultStatus(bool def) { m_default = def; }

bool Stream::IsForced() const { return m_forced; }

void Stream::SetForcedStatus(bool forced) { m_forced = forced; }

std::shared_ptr<Codec> Stream::GetCodec() const { return m_codec; }