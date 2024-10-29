#pragma once

#include "visibility.h"

namespace Alchemist::Media {
	enum class DLL_PUBLIC Type: unsigned short {
		Audio		= 1,
		Video		= 2,
		Subtitle	= 3
	};
}