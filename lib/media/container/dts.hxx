#pragma once

#include "../container.hxx"

namespace Alchemist::Media::Container {
	class DLL_PUBLIC DTS final: public Base {
		public:
			DTS();

			const std::list<Codec::Type> get_supported_codecs() const override;
	};
}