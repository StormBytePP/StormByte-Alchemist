#pragma once

#include "visibility.h"

#include <string>

namespace Alchemist::Media {
	class ALCHEMY_PUBLIC Metadata {
		public:
			Metadata() noexcept							= default;
			Metadata(const Metadata&)					= default;
			Metadata(Metadata&&) noexcept				= default;
			Metadata& operator=(const Metadata&)		= default;
			Metadata& operator=(Metadata&&) noexcept	= default;
			virtual ~Metadata() noexcept				= default;

			virtual std::string GetString() const		= 0;
	};
}