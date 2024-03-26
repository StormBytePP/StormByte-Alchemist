#pragma once

#include "../container.hxx"

namespace Alchemist::Media::Container {
	class DLL_PUBLIC Opus final: public Base {
		public:
			Opus();

			const std::list<Codec::Type> get_supported_codecs() const override;
	};
}