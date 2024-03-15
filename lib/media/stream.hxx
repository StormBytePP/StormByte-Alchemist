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
			Stream(Stream&&)					= default;
			Stream& operator=(const Stream&)	= default;
			Stream& operator=(Stream&&)			= default;
			~Stream()							= default;

			std::shared_ptr<Codec::Base> get_codec() const;
			void set_codec(std::unique_ptr<Codec::Base>);
			const std::optional<std::string>& get_language() const;
			void set_language(const std::string&);
			void set_language(std::string&&);

		protected:
			std::shared_ptr<Codec::Base> m_codec;
			std::optional<std::string> m_language;
	};
}