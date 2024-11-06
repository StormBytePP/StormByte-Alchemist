#pragma once

#include <Alchemy/media/codec.hxx>
#include <Alchemy/media/metadata.hxx>
#include <Alchemy/media/type.hxx>

#include <optional>
#include <string>

namespace Alchemist::Media {
	class ALCHEMY_PUBLIC Stream {
		public:
			Stream(const int&, const Type&) noexcept;
			Stream(const Stream&)					= default;
			Stream(Stream&&) noexcept				= default;
			Stream& operator=(const Stream&)		= default;
			Stream& operator=(Stream&&) noexcept	= default;
			virtual ~Stream() noexcept				= 0;

			const int&						GetIndex() const noexcept;
			void										SetIndex(const int&) noexcept;
			const Type&									GetType() const noexcept;
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
			int m_index;
			std::optional<std::string> m_language, m_title;
			bool m_default, m_forced;
			std::shared_ptr<Codec> m_codec;
			std::shared_ptr<Metadata> m_metadata;
			Type m_type;
	};
}