#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Codec::Audio {
	class DLL_PUBLIC Base: public Codec::Base {
		public:
			Base(const Codec::Type&);
			Base(Codec::Type&&);
			virtual ~Base() noexcept = 0;

			bool is_video() 	const noexcept override;
			bool is_audio() 	const noexcept override;
			bool is_image() 	const noexcept override;
			bool is_subtitle()	const noexcept override;

			unsigned short get_channels() const noexcept;
			void set_channels(const unsigned short&);
			void set_channels(unsigned short&&) noexcept;

		protected:
			unsigned short m_channels;
	};
}