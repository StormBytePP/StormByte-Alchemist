#pragma once

#include "item.hxx"
#include "codec.hxx"

#include <chrono>
#include <memory>
#include <optional>
#include <string>

namespace Alchemist::Media {
	class DLL_PUBLIC Stream final: public Item {
		public:
			Stream(unsigned short);

			unsigned short get_index() const noexcept;
			const std::shared_ptr<Codec::Base>& get_codec() const noexcept;
			void set_codec(std::shared_ptr<Codec::Base>) noexcept;
			const std::optional<std::string>& get_language() const noexcept;
			void set_language(const std::string&);
			void set_language(std::string&&) noexcept;
			const std::optional<std::string>& get_title() const noexcept;
			void set_title(const std::string&);
			void set_title(std::string&&) noexcept;
			const std::optional<std::string>& get_bitrate() const noexcept;
			void set_bitrate(const std::string&);
			void set_bitrate(std::string&&) noexcept;

		protected:
			unsigned short m_index;
			std::shared_ptr<Codec::Base> m_codec;
			std::optional<std::string> m_language, m_title, m_bitrate;
	};
}