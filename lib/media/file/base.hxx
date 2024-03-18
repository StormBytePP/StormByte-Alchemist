#pragma once

#include "../feature.hxx"
#include "../item.hxx"

#include <filesystem>

namespace Alchemist::Media::File {
	enum DLL_PUBLIC Status: unsigned short {
		NO_ERROR			= 0x0000,
		NOT_EXISTS			= 0x0001,
		NOT_READABLE		= 0x0002,
		NOT_WRITABLE		= 0x0004,
		DECODER_DISABLED	= 0x0008,
		ENCODER_DISABLED	= 0x0010,
	};

	class DLL_PUBLIC Base: public Item {
		public:
			Base(const std::filesystem::path&);
			Base(std::filesystem::path&&);
			Base(const Base&)					= default;
			Base(Base&&) noexcept				= default;
			Base& operator=(const Base&)		= default;
			Base& operator=(Base&&) noexcept	= default;
			~Base() noexcept					= default;

			bool has_feature(const Feature&) const noexcept;
			bool has_status(const Status&) const noexcept;

		protected:
			std::filesystem::path m_media_path;
			unsigned int m_features:2;
			unsigned int m_status:5;

		protected:
			virtual bool check()				= 0;
	};
}