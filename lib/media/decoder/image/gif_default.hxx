#pragma once

#include "../image.hxx"

namespace Alchemist::Media::Decoder::Image {
	class DLL_PUBLIC GIF_DEFAULT final: public Base {
		public:
			GIF_DEFAULT();
			GIF_DEFAULT(const GIF_DEFAULT&)				= default;
			GIF_DEFAULT(GIF_DEFAULT&&)					= default;
			GIF_DEFAULT& operator=(const GIF_DEFAULT&)	= default;
			GIF_DEFAULT& operator=(GIF_DEFAULT&&)		= default;
			~GIF_DEFAULT()								= default;
	};
}