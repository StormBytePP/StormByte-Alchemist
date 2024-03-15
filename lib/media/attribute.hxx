#pragma once

#include "visibility.h"

namespace Alchemist::Media {
	enum DLL_PUBLIC Attribute:unsigned short {
		DEFAULT		= 0x001,	/* Default option */
		HARDWARE	= 0x002,	/* Hardware accelerated */
		EXPENSIVE	= 0x004,	/* Computational expensive */
		QUALITY		= 0x008,	/* Produces more quality */
		OLD			= 0x010,	/* Considered old nowadays */
	};
}