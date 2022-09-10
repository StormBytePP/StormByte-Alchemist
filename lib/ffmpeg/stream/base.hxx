#pragma once

#include "database/data.hxx"

#include <string>
#include <list>
#include <optional>
#include <memory>

namespace StormByte::VideoConvert::Stream {
	class Base {
		public:
			Base(short stream_id, const std::string& encoder, Database::Data::stream_codec codec, char type);
			Base(const Base& codec_base);
			Base(Base&&) noexcept;
			Base& operator=(const Base& codec_base);
			Base& operator=(Base&& codec_base) noexcept;
			virtual ~Base() = default;
			inline std::unique_ptr<Base> clone() const { return std::unique_ptr<Base>(copy()); }

			virtual std::list<std::string> ffmpeg_parameters() const;
			std::string ffmpeg_stream_id() const;
			inline void set_bitrate(const std::string& bit_rate) { m_bitrate = bit_rate; }
			inline std::string get_encoder() const { return m_encoder; }
			inline Database::Data::stream_codec get_codec() const { return m_codec; }
			inline char get_type() const { return m_type; }

		protected:
			short m_stream_id;
			std::string m_encoder;
			Database::Data::stream_codec m_codec;
			char m_type;
			std::optional<std::string> m_bitrate;

			virtual Base* copy() const = 0;
	};
}