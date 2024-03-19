#pragma once

#include "../item.hxx"
#include "../codec.hxx"

#include <memory>
#include <optional>
#include <string>

namespace Alchemist::Media::Stream {
	class DLL_PUBLIC Base final: public Item {
		public:
			const std::unique_ptr<Codec::Base>& get_codec() const noexcept;
			void set_codec(std::unique_ptr<Codec::Base>) noexcept;
			const std::optional<std::string>& get_language() const noexcept;
			void set_language(const std::string&);
			void set_language(std::string&&) noexcept;

		protected:
			unsigned short m_index;
			std::unique_ptr<Codec::Base> m_codec;
			std::optional<std::string> m_language;
	};
}