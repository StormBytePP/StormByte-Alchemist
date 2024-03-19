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

			bool is_video() const noexcept;
			bool is_audio() const noexcept;
			bool is_image() const noexcept;

			const std::optional<Resolution>& get_resolution() const noexcept;
			void set_resolution(const unsigned short&, const unsigned short&);
			void set_resolution(unsigned short&&, unsigned short&&) noexcept;

		protected:
			std::optional<Resolution> m_resolution;
	};
}