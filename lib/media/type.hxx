#pragma once

#include "visibility.h"

namespace Alchemist::Media {
	enum class ALCHEMY_PUBLIC Type: unsigned short {
		Audio		= 1,
		Video		= 2,
		Subtitle	= 3
	};
}