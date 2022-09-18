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
			std::string black(const std::string& str) const			{ return colored_text(BLACK,		str); }
			std::string red(const std::string& str) const			{ return colored_text(RED,			str); }
			std::string green(const std::string& str) const			{ return colored_text(GREEN,		str); }
			std::string yellow(const std::string& str) const		{ return colored_text(YELLOW,		str); }
			std::string blue(const std::string& str) const			{ return colored_text(BLUE,			str); }
			std::string magenta(const std::string& str) const		{ return colored_text(MAGENTA,		str); }
			std::string cyan(const std::string& str) const			{ return colored_text(CYAN,			str); }
			std::string light_gray(const std::string& str) const	{ return colored_text(LIGHT_GRAY,	str); }
			std::string gray(const std::string& str) const			{ return colored_text(GRAY,			str); }
			std::string light_red(const std::string& str) const		{ return colored_text(LIGHT_RED,	str); }
			std::string light_gren(const std::string& str) const	{ return colored_text(LIGHT_GREEN,	str); }	
			std::string light_yellow(const std::string& str) const	{ return colored_text(LIGHT_YELLOW,	str); }	
			std::string light_blue(const std::string& str) const	{ return colored_text(LIGHT_BLUE,	str); }	
			std::string light_magenta(const std::string& str) const	{ return colored_text(LIGHT_MAGENTA,str); }	
			std::string light_cyan(const std::string& str) const	{ return colored_text(LIGHT_CYAN,	str); }	
			std::string white(const std::string& str) const			{ return colored_text(WHITE,		str); }	

		private:
			enum ANSI_color_code: unsigned short { BLACK=30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, LIGHT_GRAY, GRAY=90, LIGHT_RED, LIGHT_GREEN, LIGHT_YELLOW, LIGHT_BLUE, LIGHT_MAGENTA, LIGHT_CYAN, WHITE};

			inline std::string ansi_code(const ANSI_color_code& color) const							{ return "\033[" + std::to_string(color) + "m";	}
			inline std::string colored_text(const ANSI_color_code& color, const std::string& str) const	{ return ansi_code(color) + str + "\033[0m";	}
	};
}