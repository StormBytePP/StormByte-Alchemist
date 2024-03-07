#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Decoder::Image {
	class DLL_PUBLIC BMP_DEFAULT final: public Base {
		public:
			BMP_DEFAULT();
			BMP_DEFAULT(const BMP_DEFAULT&)				= default;
			BMP_DEFAULT(BMP_DEFAULT&&)					= default;
			BMP_DEFAULT& operator=(const BMP_DEFAULT&)	= default;
			BMP_DEFAULT& operator=(BMP_DEFAULT&&)		= default;
			~BMP_DEFAULT()								= default;
	};
}