#pragma once

#include "../container.hxx"

namespace Alchemist::Media::Container {
	class DLL_PUBLIC AC3 final: public Base {
		public:
			AC3();

			const std::string get_extension() const override;
			std::list<Codec::Type> get_supported_codecs() const override;
	};
}