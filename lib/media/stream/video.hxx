#pragma once

#include "../metadata/video.hxx"
#include "../stream.hxx"

namespace Alchemist::Media {
	class DLL_PUBLIC Video: public Stream {
		public:
			Video(std::shared_ptr<Codec>, const Metadata::Video&);
			Video(std::shared_ptr<Codec>&&, Metadata::Video&&);
			Video(const Video&)				= default;
			Video(Video&&)					= default;
			Video& operator=(const Video&)	= default;
			Video& operator=(Video&&)		= default;
			~Video()						= default;

			const Metadata::Video& GetMetadata() const;

		private:
			Metadata::Video m_metadata;
	};
}