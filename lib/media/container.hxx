#pragma once

#include "stream.hxx"

#include <list>
#include <memory>
#include <optional>
#include <string>

namespace Alchemist::Media::Container {
	enum DLL_PUBLIC Type:unsigned short {
		AVI, MKV, MP4, OGG, WMV,	// ALL
		AAC, AC3, DTS, MP3, OPUS, 	// Audio
									// Image containers unimplemented
		UNKNOWN = std::numeric_limits<unsigned short>::max()
	};
	
	class DLL_PUBLIC Base: public Item {
		public:
			Base(const Type&, std::string&&);
			Base(const Type&, std::string&&, const unsigned short&);
			virtual ~Base() noexcept 									= 0;

			void add_stream(const Stream&);
			void add_stream(Stream&&);
			const std::list<Stream>& get_streams() const;

			const std::string& get_extension() const noexcept;
			const std::list<Codec::Type>& get_supported_codecs() const noexcept;
			const std::optional<unsigned short>& get_max_streams() const noexcept;

		protected:
			Type m_type;
			std::string m_extension;
			std::optional<unsigned short> m_max_streams;
			const std::list<Codec::Type> m_supported_codecs;
			std::list<Stream> m_streams;

		private:
			void sort_streams();
	};

	std::shared_ptr<Base> DLL_PUBLIC Instance(const Type&);
	std::shared_ptr<Base> DLL_PUBLIC Instance(const std::string&, std::shared_ptr<Base>);
}