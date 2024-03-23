#pragma once

#include "../video.hxx"

namespace Alchemist::Media::Codec::Video {
	class DLL_PUBLIC Unknown final: public Base {
		public:
			Unknown(const std::string&, const std::string&);

			std::list<Decoder::Type> get_available_decoders() const override;
			std::list<Encoder::Type> get_available_encoders() const override;

			std::string get_name() const override;
			std::string get_long_name() const override;

		private:
			std::string m_name, m_long_name;
	};
}