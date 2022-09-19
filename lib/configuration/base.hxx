#pragma once

#include "types.hxx"

#include <map>
#include <list>

namespace StormByte::VideoConvert::Configuration {
	class Base {
		public:
			Base(const std::list<std::string>& mandatory_string, const std::list<std::string>& mandatory_int, const std::list<std::string>& optional_string, const std::list<std::string>& optional_int);
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			virtual ~Base() = default;

			virtual bool check() const = 0;
			void parse(const Types::path_t&) noexcept;
			void merge(const Base& config);
			void merge(Base&& config) noexcept;
			bool have_all_mandatory_values() const;
			inline const std::map<std::string, std::string>& get_errors() const { return m_errors; }

		protected:
			inline std::optional<int> get_int_value(const std::string& key) 				{ return m_values_int.contains(key) ? m_values_int.at(key) : std::optional<int>(); }
			inline std::optional<std::string> get_string_value(const std::string& key)		{ return m_values_int.contains(key) ? m_values_string.at(key) : std::optional<std::string>(); }
			inline void set_int_value(const std::string& key, const int& value)				{ m_values_int.emplace(key, value); m_errors.erase(key); }
			inline void set_string_value(const std::string& key, const std::string& value)	{ m_values_string.emplace(key, value); m_errors.erase(key); }
			inline void set_string_value(const std::string& key, std::string&& value)		{ m_values_string.emplace(key, std::move(value)); m_errors.erase(key); }

			std::map<std::string, std::string> m_values_string;
			std::map<std::string, int> m_values_int;
			mutable std::map<std::string, std::string> m_errors;

		private:
			const std::list<std::string> m_mandatory_string_values;
			const std::list<std::string> m_mandatory_int_values;
			const std::list<std::string> m_optional_string_values;
			const std::list<std::string> m_optional_int_values;
	};
}
