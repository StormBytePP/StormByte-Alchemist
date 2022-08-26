#pragma once

#include <string>
#include <list>
#include <optional>

namespace StormByte::VideoConvert::Stream {
	class Base {
		public:
			Base(unsigned short stream_id, const std::string& encoder);
			Base(const Base& codec_base);
			Base(Base&&) = default;
			Base& operator=(const Base& codec_base);
			virtual ~Base() = default;
			virtual Base* copy() const = 0;

			virtual std::list<std::string> ffmpeg_parameters() const = 0;
			inline void set_bitrate(const std::string& bit_rate) { m_bitrate = bit_rate; }
			inline std::string get_encoder() const { return m_encoder; }

		protected:
			unsigned short m_stream_id;
			std::string m_encoder;
			std::optional<std::string> m_bitrate;
	};
}