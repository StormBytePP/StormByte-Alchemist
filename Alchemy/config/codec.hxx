#pragma once

#include <Alchemy/visibility.h>

#include <list>
#include <optional>
#include <string>

namespace Alchemy::Config {
	struct ALCHEMY_PUBLIC Codec {
		Codec(const std::string&);
		std::string														c_name;
		std::optional<int> 												c_bitrate;
		std::optional<std::string> 										c_options;
		std::optional<std::list<std::pair<std::string, std::string>>>	c_ffmpeg;
	};
}