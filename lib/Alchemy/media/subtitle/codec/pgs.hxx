#pragma once

#include <Alchemy/media/subtitle/codec.hxx>

namespace Alchemist::Media::Subtitle {
	class ALCHEMY_PUBLIC PGS: public Codec {
		public:
			PGS() noexcept;
			PGS(const PGS&)				= default;
			PGS(PGS&&)					= default;
			PGS& operator=(const PGS&)	= default;
			PGS& operator=(PGS&&)		= default;
			~PGS() noexcept				= default;
	};
}