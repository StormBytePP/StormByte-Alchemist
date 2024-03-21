#pragma once

#include "codec.hxx"

#include <list>
#include <memory>
#include <string>

namespace Alchemist::Media::Container {
	enum DLL_PUBLIC Type:unsigned short {
		AVI, MKV, MP4, OGG, // Video
		AAC, DTS, MP2, MP3, OPUS, // Audio
		BMP, GIF, JPG, PNG, TIFF, WEBP, // Image
		GENERIC = std::numeric_limits<unsigned short>::max()
	};
	
	class DLL_PUBLIC Base: public Item {
		public:
			Base(const std::string&);
			Base(std::string&&);
			virtual ~Base() noexcept 									= default;

			const std::string& get_extension() const;
			virtual std::list<Codec::Type> get_supported_codecs() const	= 0;

		protected:
			std::string m_extension;
	};

	std::shared_ptr<Base> DLL_PUBLIC Instance(const Type&);
	std::shared_ptr<Base> DLL_PUBLIC Instance(const std::string&);
}