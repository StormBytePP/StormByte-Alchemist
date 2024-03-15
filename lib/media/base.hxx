#pragma once

#include "visibility.h"

namespace Alchemist::Media {
	enum DLL_PUBLIC Attribute:unsigned short {
		HARDWARE	= 0x000,	/* Hardware accelerated */
		EXPENSIVE	= 0x001,	/* Computational expensive */
		QUALITY		= 0x002,	/* Produces more quality */
		DEFAULT		= 0x004,	/* Default option */
		OLD			= 0x008,	/* Considered old nowadays */
	};
}