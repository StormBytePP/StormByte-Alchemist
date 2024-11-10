#pragma once

#include <Alchemy/visibility.h>

#include <filesystem>
#include <optional>
#include <vector>

namespace Alchemy::Media { class Stream; }

namespace Alchemy::Database {
	class ALCHEMY_PUBLIC File {
		public:
			File()							= default;
			File(const File&)				= default;
			File(File&&)					= default;
			File& operator=(const File&)	= default;
			File& operator=(File&&)			= default;
			~File()							= default;

			int													GetFilmID() const noexcept;
			void												SetFilmID(const int&);
			const std::filesystem::path&						GetInFile() const noexcept;
			void												SetInFile(const std::filesystem::path&);
			void												SetInFile(std::filesystem::path&&);
			const std::filesystem::path&						GetOutFile() const noexcept;
			void												SetOutFile(const std::filesystem::path&);
			void												SetOutFile(std::filesystem::path&&);
			unsigned long long									GetInSize() const noexcept;
			void												SetInSize(const unsigned long long&);
			const std::optional<unsigned long long>&			GetOutSize() const noexcept;
			void												SetOutSize(const unsigned long long&);
			const std::optional<unsigned int>&					GetEncodeTime() const noexcept;
			void												SetEncodeTime(const int&);
			const int&											GetPriority() const noexcept;
			void												SetPriority(const int&);
			bool												GetActiveStatus() const noexcept;
			void												SetActiveStatus(bool);
			bool												GetEnabledStatus() const noexcept;
			void												SetEnabledStatus(bool);
			bool												GetFailedStatus() const noexcept;
			void												SetFailedStatus(bool);
			const std::vector<std::shared_ptr<Media::Stream>>&	GetStreams() const noexcept;
			void												AddStream(std::shared_ptr<Media::Stream>);

		private:
			int m_film_id;
			std::filesystem::path m_in_file, m_out_file;
			unsigned long long m_in_size;
			std::optional<unsigned long long> m_out_size;
			std::optional<unsigned int> m_encode_time;
			int m_priority;
			bool m_active, m_enabled, m_failed;
			std::vector<std::shared_ptr<Media::Stream>> m_streams;
	};
}