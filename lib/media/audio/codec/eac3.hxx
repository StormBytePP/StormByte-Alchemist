#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Audio {
	class ALCHEMY_PUBLIC EAC3: public Codec {
		public:
			EAC3() noexcept;
			EAC3(const EAC3&)				= default;
			EAC3(EAC3&&)					= default;
			EAC3& operator=(const EAC3&)	= default;
			EAC3& operator=(EAC3&&)		= default;
			~EAC3() noexcept				= default;
	};
}