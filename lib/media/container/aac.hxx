#pragma once

#include "../container.hxx"

namespace Alchemist::Media::Container {
	class DLL_PUBLIC AAC final: public Base {
		public:
			AAC();

			const std::list<Codec::Type> get_supported_codecs() const override;
	};
}