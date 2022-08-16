#pragma once

#include "../base.hxx"

namespace StormByte::VideoConvert::Stream::Video {
	class Base: public StormByte::VideoConvert::Stream::Base {
		public:
			Base(unsigned short stream_id, const std::string& encoder);
			Base(const Base& copy);
			Base& operator=(const Base& base);
			virtual ~Base() = default;
			
			virtual std::list<std::string> ffmpeg_parameters() const;
			inline void set_tune_animation() { m_is_animation = true; }
			inline void set_max_rate(const std::string& max_rate) { m_max_rate = max_rate; }

		protected:
			bool m_is_animation;
			std::optional<std::string> m_max_rate;

		private:
			static const bool IS_ANIMATION_DEFAULT;
	};
}