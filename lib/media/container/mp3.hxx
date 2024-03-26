#pragma once

#include "../container.hxx"

namespace Alchemist::Media::Container {
	class DLL_PUBLIC MP3 final: public Base {
		public:
			MP3();

			const std::list<Codec::Type> get_supported_codecs() const override;
	};
}