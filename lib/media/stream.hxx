#pragma once

#include "codec.hxx"

#include <optional>
#include <string>

namespace Alchemist::Media {
	class DLL_PUBLIC Stream {
		public:
			Stream(std::shared_ptr<Media::Codec>);
			Stream(const Stream&)					= default;
			Stream(Stream&&)						= default;
			Stream& operator=(const Stream&)		= default;
			Stream& operator=(Stream&&)				= default;
			virtual ~Stream()						= 0;

			const std::optional<std::string>& GetLanguage() const;
			void SetLanguage(const std::string&);
			const std::optional<std::string>& GetTitle() const;
			void SetTitle(const std::string&);
			bool IsDefault() const;
			void SetDefaultStatus(bool);
			bool IsForced() const;
			void SetForcedStatus(bool);
			std::shared_ptr<Codec> GetCodec() const;
			
		protected:
			std::optional<std::string> m_language, m_title;
			bool m_default, m_forced;
			std::shared_ptr<Codec> m_codec;
	};
}