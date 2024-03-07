#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Decoder::Video {
	class DLL_PUBLIC AV1_DEFAULT final: public Base {
		public:
			AV1_DEFAULT();
			AV1_DEFAULT(const AV1_DEFAULT&)				= default;
			AV1_DEFAULT(AV1_DEFAULT&&)					= default;
			AV1_DEFAULT& operator=(const AV1_DEFAULT&)	= default;
			AV1_DEFAULT& operator=(AV1_DEFAULT&&)		= default;
			~AV1_DEFAULT()								= default;
	};
}