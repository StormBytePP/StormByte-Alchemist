#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Codec::Video {
	struct DLL_PUBLIC Resolution {
		unsigned short width;
		unsigned short height;
	};
	
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

			const std::optional<Resolution>& get_resolution() const;
			void set_resolution(const unsigned short&, const unsigned short&);
			void set_resolution(unsigned short&&, unsigned short&&);

		protected:
			std::optional<Resolution> m_resolution;
	};
}