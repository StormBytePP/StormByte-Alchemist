#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC Base: public Codec::Base {
		public:
			Base(const Codec::Type&);
			Base(Codec::Type&&);
			Base(const Base&)				= default;
			Base(Base&&)					= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&)			= default;
			virtual ~Base()					= default;

			bool is_video() const;
			bool is_audio() const;
			bool is_image() const;
	};
}