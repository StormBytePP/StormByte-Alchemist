#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Encoder::Video {
	class DLL_PUBLIC AV1_RAV1E final: public Base {
		public:
			AV1_RAV1E();
			AV1_RAV1E(const AV1_RAV1E&)					= default;
			AV1_RAV1E(AV1_RAV1E&&) noexcept				= default;
			AV1_RAV1E& operator=(const AV1_RAV1E&)		= default;
			AV1_RAV1E& operator=(AV1_RAV1E&&) noexcept	= default;
			~AV1_RAV1E() noexcept						= default;
	};
}