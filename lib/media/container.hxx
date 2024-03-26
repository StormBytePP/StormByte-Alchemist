#pragma once

#include "stream.hxx"

#include <list>
#include <memory>
#include <optional>
#include <string>

namespace Alchemist::Media::Container {
	enum DLL_PUBLIC Type:unsigned short {
		AVI, MKV, MP4, OGG,	// ALL
		AAC, AC3, DTS, MP3, OPUS, 	// Audio
									// Image containers unimplemented
		UNKNOWN = std::numeric_limits<unsigned short>::max()
	};
	
	class DLL_PUBLIC Base: public Item {
		public:
			Base(const Type&, std::string&&);
			Base(const Type&, std::string&&, const unsigned short&);
			virtual ~Base() noexcept 											= default;

			void add_stream(const Stream&);
			void add_stream(Stream&&);
			const std::list<Stream>& get_streams() const;

			const std::string& get_extension() const noexcept;
			const std::optional<unsigned short>& get_max_streams() const noexcept;
			virtual const std::list<Codec::Type> get_supported_codecs() const			= 0;

		protected:
			const Type m_type;
			const std::string m_extension;
			const std::optional<unsigned short> m_max_streams;

		private:
			std::list<Stream> m_streams;
			void sort_streams();
	};

	std::shared_ptr<Base> DLL_PUBLIC Instance(const Type&);
	std::shared_ptr<Base> DLL_PUBLIC Instance(const std::string&, std::shared_ptr<Base>);
}