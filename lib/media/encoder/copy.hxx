#pragma once

#include "../encoder.hxx"

namespace Alchemist::Media::Encoder {
	class DLL_PUBLIC Copy final: public Base {
		public:
			Copy();
			Copy(const Copy&)				= default;
			Copy(Copy&&) noexcept			= default;
			Copy& operator=(const Copy&)	= default;
			Copy& operator=(Copy&&) noexcept= default;
			~Copy() noexcept				= default;
	};
}