#pragma once

#include "../base.hxx"

namespace StormByte::VideoConvert::Stream::Audio {
	class Base: public StormByte::VideoConvert::Stream::Base {
		public:
			Base(const unsigned short& stream_id, const std::string& encoder, const Database::Data::film::stream::codec& codec);
			Base(unsigned short&& stream_id, std::string&& encoder, Database::Data::film::stream::codec&& codec);
			Base(const Base& base) = default;
			Base(Base&& base) noexcept = default;
			Base& operator=(const Base& base) = default;
			Base& operator=(Base&& base) noexcept = default;
			virtual ~Base() = default;

			virtual void SetChannels(const int& channels);
			std::list<std::string> ffmpeg_parameters() const override;

		protected:
			std::optional<int> m_channels;
	};
}
