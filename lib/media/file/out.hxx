#pragma once

#include "../file.hxx"

namespace Alchemist::Media {
	class Stream;
	class DLL_PUBLIC OutFile: public File {
		public:
			OutFile(const std::filesystem::path&);
			OutFile(std::filesystem::path&&);
			OutFile(const OutFile&)				= default;
			OutFile(OutFile&&)					= default;
			OutFile& operator=(const OutFile&)	= default;
			OutFile& operator=(OutFile&&)		= default;
			~OutFile()							= default;

			void 					AddStream(std::shared_ptr<Stream>);
			const unsigned int& 	GetFilmID() const noexcept;
			void					SetFilmID(const unsigned int&);
			const unsigned short&	GetPriority() const noexcept;
			void					SetPriority(const unsigned short&);

		private:
			unsigned int m_film_id;
			unsigned short m_priority;
	};
}