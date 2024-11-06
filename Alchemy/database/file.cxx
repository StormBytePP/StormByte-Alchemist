#include <Alchemy/database/file.hxx>

using namespace Alchemist::Database;

int	File::GetFilmID() const noexcept { return m_film_id; }

void File::SetFilmID(const int& film_id) { m_film_id = film_id; }

const std::filesystem::path& File::GetInFile() const noexcept { return m_in_file; }

void File::SetInFile(const std::filesystem::path& in_file) { m_in_file = in_file; }

void File::SetInFile(std::filesystem::path&& in_file) { m_in_file = std::move(in_file); }

const std::filesystem::path& File::GetOutFile() const noexcept { return m_out_file; }

void File::SetOutFile(const std::filesystem::path& out_file) { m_out_file = out_file; }

void File::SetOutFile(std::filesystem::path&& out_file) { m_out_file = std::move(out_file); }

unsigned long long File::GetInSize() const noexcept { return m_in_size; }

void File::SetInSize(const unsigned long long& in_size) { m_in_size = in_size; }

const std::optional<unsigned long long>& File::GetOutSize() const noexcept { return m_out_size; }

void File::SetOutSize(const unsigned long long& out_size) { m_out_size = out_size; }

const std::optional<unsigned int>& File::GetEncodeTime() const noexcept { return m_encode_time; }

void File::SetEncodeTime(const int& encode_time) { m_encode_time = encode_time; }

const int& File::GetPriority() const noexcept { return m_priority; }

void File::SetPriority(const int& priority) { m_priority = priority; }

bool File::GetActiveStatus() const noexcept { return m_active; }

void File::SetActiveStatus(bool active) { m_active = active; }

bool File::GetEnabledStatus() const noexcept { return m_enabled; }

void File::SetEnabledStatus(bool enabled) { m_enabled = enabled; }

bool File::GetFailedStatus() const noexcept { return m_failed; }

void File::SetFailedStatus(bool failed) { m_failed = failed; }

const std::vector<std::shared_ptr<Alchemist::Media::Stream>>& File::GetStreams() const noexcept { return m_streams; }

void File::AddStream(std::shared_ptr<Alchemist::Media::Stream> stream) { m_streams.push_back(stream); }