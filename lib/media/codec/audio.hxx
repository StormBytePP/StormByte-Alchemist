#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC Base: public Codec::Base {
		public:
			Base(const Codec::Type&);
			Base(Codec::Type&&);

			bool is_video() const noexcept;
			bool is_audio() const noexcept;
			bool is_image() const noexcept;

			unsigned short get_channels() const noexcept;
			void set_channels(const unsigned short&);
			void set_channels(unsigned short&&) noexcept;

		protected:
			unsigned short m_channels;
	};
}