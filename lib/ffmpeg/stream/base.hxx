#pragma once

#include "database/data.hxx"

#include <string>
#include <list>
#include <optional>
#include <memory>

namespace StormByte::VideoConvert::Stream {
	class Base {
		public:
			Base(const short& stream_id, const std::string& encoder, const Database::Data::film::stream::codec& codec, const char& type);
			Base(short&& stream_id, std::string&& encoder, Database::Data::film::stream::codec&& codec, char&& type);
			Base(const Base& codec_base) = default;
			Base(Base&&) noexcept = default;
			Base& operator=(const Base& codec_base) = default;
			Base& operator=(Base&& codec_base) noexcept = default;
			virtual ~Base() = default;
			inline std::unique_ptr<Base> clone() const { return std::unique_ptr<Base>(copy()); }

			virtual std::list<std::string> ffmpeg_parameters() const;
			std::string ffmpeg_stream_id() const;
			std::string ffmpeg_stream_pos() const;
 			inline void set_bitrate(const std::string& bit_rate) { m_bitrate = bit_rate; }
			inline std::string get_encoder() const { return m_encoder; }
			inline Database::Data::film::stream::codec get_codec() const { return m_codec; }
			inline char get_type() const { return m_type; }
			inline void set_stream_position(const unsigned short& pos) { m_stream_position = pos; }

		protected:
			short m_stream_id;
			unsigned short m_stream_position;
			std::string m_encoder;
			Database::Data::film::stream::codec m_codec;
			char m_type;
			std::optional<std::string> m_bitrate;

			virtual Base* copy() const = 0;
	};
}