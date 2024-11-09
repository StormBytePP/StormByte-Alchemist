#pragma once

#include <Alchemy/media/metadata.hxx>

#include <string>

namespace Alchemy::Media::Subtitle {
	class ALCHEMY_PUBLIC Metadata: public Media::Metadata {
		public:
			Metadata(const std::string&);
			Metadata(std::string&&) noexcept;
			Metadata(const Metadata&)					= default;
			Metadata(Metadata&&) noexcept				= default;
			Metadata& operator=(const Metadata&)		= default;
			Metadata& operator=(Metadata&&) noexcept	= default;
			~Metadata() noexcept						= default;

			std::string GetString() const final;

		private:
			std::string m_encoding;
	};
}