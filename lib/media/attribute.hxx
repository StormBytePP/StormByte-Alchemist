#pragma once

#include "visibility.h"

namespace Alchemist::Media {
	enum DLL_PUBLIC Attribute:unsigned short {
		DEFAULT		= 0x001,	/* Default option */
		EXPENSIVE	= 0x002,	/* Computational expensive */
		HARDWARE	= 0x004,	/* Hardware accelerated */
		OLD			= 0x008,	/* Considered old nowadays */
		QUALITY		= 0x010,	/* Produces more quality */
	};
}