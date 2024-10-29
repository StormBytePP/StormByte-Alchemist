#pragma once

#include "codec.hxx"
#include "metadata.hxx"

#include <optional>
#include <string>

namespace Alchemist::Media {
	class DLL_PUBLIC Stream {
		public:
			Stream(const unsigned short&, const char&) noexcept;
			Stream(const Stream&)					= default;
			Stream(Stream&&) noexcept				= default;
			Stream& operator=(const Stream&)		= default;
			Stream& operator=(Stream&&) noexcept	= default;
			virtual ~Stream() noexcept				= 0;

			const unsigned short&						GetIndex() const noexcept;
			void										SetIndex(const unsigned short&) noexcept;
			const char&									GetType() const noexcept;
			const std::optional<std::string>& 			GetLanguage() const noexcept;
			void 										SetLanguage(const std::string&);
			const std::optional<std::string>& 			GetTitle() const noexcept;
			void 										SetTitle(const std::string&);
			bool 										IsDefault() const noexcept;
			void 										SetDefaultStatus(bool);
			bool 										IsForced() const noexcept;
			void 										SetForcedStatus(bool);
			const std::shared_ptr<Codec>& 				GetCodec() const noexcept;
			void										SetCodec(std::shared_ptr<Codec>) noexcept;
			const std::shared_ptr<Metadata>&			GetMetadata() const noexcept;
			
		protected:
			unsigned short m_index;
			std::optional<std::string> m_language, m_title;
			bool m_default, m_forced;
			std::shared_ptr<Codec> m_codec;
			std::shared_ptr<Metadata> m_metadata;
			char m_type;
	};
}