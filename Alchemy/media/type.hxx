#pragma once

#include <Alchemy/visibility.h>

namespace Alchemy::Media {
	enum class ALCHEMY_PUBLIC Type: int {
		Audio		= 1,
		Video		= 2,
		Subtitle	= 3
	};
}