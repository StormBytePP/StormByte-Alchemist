#pragma once

#include "../container.hxx"

namespace Alchemist::Media::Container {
	class DLL_PUBLIC Unknown final: public Base {
		public:
			Unknown(std::string&& ext);

			const std::list<Codec::Type> get_supported_codecs() const override;
	};
}