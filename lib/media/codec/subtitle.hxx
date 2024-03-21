#pragma once

#include "../codec.hxx"

namespace Alchemist::Media::Codec::Subtitle {	
	class DLL_PUBLIC Base: public Codec::Base {
		public:
			Base(const Codec::Type&);
			Base(Codec::Type&&);
			virtual ~Base() noexcept = 0;

			bool is_video() 	const noexcept override;
			bool is_audio() 	const noexcept override;
			bool is_image() 	const noexcept override;
			bool is_subtitle()	const noexcept override;

			const std::string& get_name() const noexcept;
			void set_name(const std::string&);
			void set_name(std::string&&);
			const std::string& get_long_name() const noexcept;
			void set_long_name(const std::string&);
			void set_long_name(std::string&&);

		protected:
			std::string m_name, m_long_name;
	};
}