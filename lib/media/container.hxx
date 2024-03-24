#pragma once

#include "stream.hxx"

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
			virtual ~Base() noexcept 									= default;

			virtual const std::string get_extension() const				= 0;
			virtual std::list<Codec::Type> get_supported_codecs() const	= 0;
			const std::list<Stream>& get_streams() const;
			void add_stream(const Stream&);
			void add_stream(Stream&&);

		protected:
			std::list<Stream> m_streams;

		private:
			void sort_streams();
	};

	std::shared_ptr<Base> DLL_PUBLIC Instance(const Type&);
	std::shared_ptr<Base> DLL_PUBLIC Instance(const std::string&);
}