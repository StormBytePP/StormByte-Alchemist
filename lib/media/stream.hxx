#pragma once

#include "codec.hxx"

#include <list>

namespace Alchemist::Media {
	class DLL_PUBLIC Stream: public Item {
		public:
			Stream()							= default;
			Stream(const Stream&)				= default;
			Stream(Stream&&)					= default;
			Stream& operator=(const Stream&)	= default;
			Stream& operator=(Stream&&)			= default;
			~Stream()							= default;

		private:
			std::list<Codec::Base> m_in_codecs, m_out_codecs;
	};
}