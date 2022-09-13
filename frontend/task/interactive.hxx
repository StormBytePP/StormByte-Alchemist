#pragma once

#include "base.hxx"

namespace StormByte::VideoConvert::Task {
	class Interactive: public Base {
		public:
			Interactive(std::filesystem::path&& path);
			Interactive(const Interactive& interactive) = delete;
			Interactive(Interactive&& interactive) noexcept = delete;
			Interactive& operator=(const Interactive& interactive) = delete;
			Interactive& operator=(Interactive&& interactive) noexcept = delete;
			~Interactive() noexcept = default;

			static Interactive& get_instance();

			STATUS run(std::shared_ptr<Configuration> config) noexcept override;

		private:
			Interactive();
			std::optional<std::list<Database::Data::film>> ask_film_data() const;
			std::list<Database::Data::film::stream> ask_streams();
			Database::Data::film::stream ask_stream(const char& codec_type) const;
			bool add_films_to_database(const std::list<Database::Data::film>& films);
			#ifdef ENABLE_HEVC // HDR is only available if HEVC/H265 is supported
			Database::Data::film::stream::hdr ask_stream_hdr() const;
			#endif
			static void signal_handler(int);
	};
}