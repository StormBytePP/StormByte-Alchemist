#pragma once

#include "visibility.hxx"

#include <optional>
#include <string>

namespace StormByte::VideoConvert::Media {
	class DLL_PUBLIC Properties {
		public:
			Properties()								= default;
			Properties(const Properties&)				= default;
			Properties(Properties&&)					= default;
			Properties& operator=(const Properties&)	= default;
			Properties& operator=(Properties&&)			= default;
			~Properties()								= default;

			inline std::optional<std::string> get_language() const;
			inline void set_language(const std::string&);
			inline void set_language(std::string&&);

		protected:
			std::optional<std::string> m_language;
	};
}