#pragma once

#include "visibility.h"

namespace Alchemist::Media {
	enum DLL_PUBLIC Feature:unsigned short {
		HDR			= 0x0001, /* HDR10		*/
		HDR_PLUS	= 0x0002, /* HDR10+		*/ 
	};
}