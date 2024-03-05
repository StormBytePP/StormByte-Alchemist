#pragma once

#include "media/media.hxx"

namespace StormByte::VideoConvert::Media::Codec {
	class DLL_LOCAL Base {
		public:
			Base(const unsigned short& codec_id);
			Base(unsigned short&& codec_id);
			Base(const Base&)				= default;
			Base(Base&&)					= default;
			Base& operator=(const Base&)	= default;
			Base& operator=(Base&&)			= default;
			virtual ~Base()					= 0;

			inline unsigned short get_codec_id() const;
			bool is_video() const;
			bool is_audio() const;
			bool is_image() const;
		
		protected:
			unsigned short m_codec_id;
	};
}
