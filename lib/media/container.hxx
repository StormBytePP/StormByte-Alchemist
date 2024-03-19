#pragma once

#include "codec.hxx"

#include <filesystem>
#include <list>
#include <string>

namespace Alchemist::Media::Container {
	enum DLL_PUBLIC Type:unsigned short {
		AVI, MKV, MP4, OGG, // Video
		AAC, DTS, MP2, MP3, OPUS, // Audio
		BMP, GIF, JPG, PNG, TIFF, WEBP // Image
	};
	
	class DLL_PUBLIC Base: public Item {
		public:
			Base(const std::filesystem::path&);
			Base(std::filesystem::path&&);

			std::filesystem::path get_file_path() const;
			virtual std::list<Codec::Type> get_supported_codecs() const	= 0;

		protected:
			std::filesystem::path m_file_path;
	};
}