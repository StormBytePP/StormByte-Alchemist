#pragma once

#include "../feature.hxx"
#include "../stream/base.hxx"

#include <filesystem>
#include <list>
#include <memory>

namespace Alchemist::Media::Stream { class Base; }

namespace Alchemist::Media::File {
	enum DLL_PUBLIC Status: unsigned short {
		NO_ERROR			= 0x0000,
		NOT_EXISTS			= 0x0001,
		NOT_READABLE		= 0x0002,
		NOT_WRITABLE		= 0x0004,
		DECODER_DISABLED	= 0x0008,
		ENCODER_DISABLED	= 0x0010,
		STREAM_ERROR		= 0x0012
	};

	class DLL_PUBLIC Base: public Item {
		public:
			Base(const std::filesystem::path&);
			Base(std::filesystem::path&&);

			bool has_feature(const Feature&) const noexcept;
			bool has_status(const Status&) const noexcept;

			const std::list<std::unique_ptr<Media::Stream::Base>>& get_streams() const noexcept;

		protected:
			std::filesystem::path m_media_path;
			std::list<std::unique_ptr<Media::Stream::Base>> m_streams;
			unsigned int m_features:2;
			unsigned int m_status:5;

		private:
			virtual void update()				= 0;
	};
}