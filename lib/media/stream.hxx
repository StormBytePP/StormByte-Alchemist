#pragma once

#include "codec.hxx"

#include <memory>
#include <optional>
#include <string>

namespace Alchemist::Media {
	class DLL_PUBLIC Stream final: public Item {
		public:
			Stream()							= default;
			Stream(const Stream&)				= default;
			Stream(Stream&&) noexcept			= default;
			Stream& operator=(const Stream&)	= default;
			Stream& operator=(Stream&&) noexcept= default;
			~Stream() noexcept					= default;

			std::shared_ptr<Codec::Base> get_codec() const noexcept;
			void set_codec(std::unique_ptr<Codec::Base>) noexcept;
			const std::optional<std::string>& get_language() const noexcept;
			void set_language(const std::string&);
			void set_language(std::string&&) noexcept;

		protected:
			std::shared_ptr<Codec::Base> m_codec;
			std::optional<std::string> m_language;
	};
}