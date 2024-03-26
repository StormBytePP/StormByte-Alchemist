#pragma once

#include "../container.hxx"

namespace Alchemist::Media::Container {
	class DLL_PUBLIC AC3 final: public Base {
		public:
			AC3();

			const std::list<Codec::Type> get_supported_codecs() const override;
	};
}