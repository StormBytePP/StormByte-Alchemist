#pragma once

#include "codec.hxx"

#include <optional>
#include <string>

namespace Alchemist::Media {
	class DLL_PUBLIC Stream {
		public:
			Stream(std::shared_ptr<Media::Codec>);
			Stream(const Stream&)					= default;
			Stream(Stream&&) noexcept				= default;
			Stream& operator=(const Stream&)		= default;
			Stream& operator=(Stream&&) noexcept	= default;
			virtual ~Stream() noexcept				= 0;

			const std::optional<std::string>& GetLanguage() const noexcept;
			void SetLanguage(const std::string&);
			const std::optional<std::string>& GetTitle() const noexcept;
			void SetTitle(const std::string&);
			bool IsDefault() const noexcept;
			void SetDefaultStatus(bool);
			bool IsForced() const noexcept;
			void SetForcedStatus(bool);
			const std::shared_ptr<Codec>& GetCodec() const noexcept;
			
		protected:
			std::optional<std::string> m_language, m_title;
			bool m_default, m_forced;
			std::shared_ptr<Codec> m_codec;
	};
}