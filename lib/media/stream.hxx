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
			const std::shared_ptr<Codec::Base>& get_codec() const noexcept;
			void set_codec(std::shared_ptr<Codec::Base>) noexcept;
			const std::optional<std::string>& get_language() const noexcept;
			void set_language(const std::string&);
			void set_language(std::string&&) noexcept;
			const std::optional<std::string>& get_title() const noexcept;
			void set_title(const std::string&);
			void set_title(std::string&&) noexcept;
			const std::optional<unsigned int>& get_frame_number() const noexcept;
			void set_frame_number(const unsigned int&);
			void set_frame_number(unsigned int&&) noexcept;
			const std::optional<unsigned long>& get_bytes() const noexcept;
			void set_bytes(const unsigned long&);
			void set_bytes(unsigned long&&) noexcept;
			const std::optional<std::string>& get_duration() const noexcept;
			void set_duration(const std::string&);
			void set_duration(std::string&&) noexcept;

		protected:
			unsigned short m_index;
			std::shared_ptr<Codec::Base> m_codec;
			std::optional<std::string> m_language, m_title, m_duration;
			std::optional<unsigned int> m_frame_number;
			std::optional<unsigned long> m_bytes;
	};
}