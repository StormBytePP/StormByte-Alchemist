#pragma once

#include "../container.hxx"

namespace Alchemist::Media::Container {
	class DLL_PUBLIC WMV final: public Base {
		public:
			WMV();

			const std::list<Codec::Type> get_supported_codecs() const override;
	};
}