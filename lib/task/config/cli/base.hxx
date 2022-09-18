#pragma once

#include "../base.hxx"

#include <iostream>

namespace StormByte::VideoConvert::Task::Config::CLI {	
	class Base: public Task::Config::Base {
		public:
			Base(Types::config_t config, const unsigned short& req_mask = 0);
			Base(const Base&) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base&) = default;
			Base& operator=(Base&&) noexcept = default;
			virtual ~Base() noexcept = 0;

		protected:
			/* Color functions for convenience */
			template <typename T> inline std::string black(const T& str) const			{ return colored_text(BLACK,		str); }
			template <typename T> inline std::string red(const T& str) const			{ return colored_text(RED,			str); }
			template <typename T> inline std::string green(const T& str) const			{ return colored_text(GREEN,		str); }
			template <typename T> inline std::string yellow(const T& str) const			{ return colored_text(YELLOW,		str); }
			template <typename T> inline std::string blue(const T& str) const			{ return colored_text(BLUE,			str); }
			template <typename T> inline std::string magenta(const T& str) const		{ return colored_text(MAGENTA,		str); }
			template <typename T> inline std::string cyan(const T& str) const			{ return colored_text(CYAN,			str); }
			template <typename T> inline std::string light_gray(const T& str) const		{ return colored_text(LIGHT_GRAY,	str); }
			template <typename T> inline std::string gray(const T& str) const			{ return colored_text(GRAY,			str); }
			template <typename T> inline std::string light_red(const T& str) const		{ return colored_text(LIGHT_RED,	str); }
			template <typename T> inline std::string light_green(const T& str) const	{ return colored_text(LIGHT_GREEN,	str); }	
			template <typename T> inline std::string light_yellow(const T& str) const	{ return colored_text(LIGHT_YELLOW,	str); }	
			template <typename T> inline std::string light_blue(const T& str) const		{ return colored_text(LIGHT_BLUE,	str); }	
			template <typename T> inline std::string light_magenta(const T& str) const	{ return colored_text(LIGHT_MAGENTA,str); }	
			template <typename T> inline std::string light_cyan(const T& str) const		{ return colored_text(LIGHT_CYAN,	str); }	
			template <typename T> inline std::string white(const T& str) const			{ return colored_text(WHITE,		str); }	

			/* Those remain protected in case derived classes want to make any advanced usage */
			enum ANSI_color_code: unsigned short { BLACK=30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, LIGHT_GRAY, GRAY=90, LIGHT_RED, LIGHT_GREEN, LIGHT_YELLOW, LIGHT_BLUE, LIGHT_MAGENTA, LIGHT_CYAN, WHITE};

			inline std::string ansi_code(const ANSI_color_code& color) const							{ return "\033[" + std::to_string(color) + "m";	}
			inline std::string colored_text(const ANSI_color_code& color, const std::string& str) const	{ return ansi_code(color) + str + "\033[0m";	}
			inline std::string colored_text(const ANSI_color_code& color, const int& number) const		{ return colored_text(color, std::to_string(number)); }
	};
}