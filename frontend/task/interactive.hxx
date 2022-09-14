#pragma once

#include "task/base.hxx"
#include "ffprobe/ffprobe.hxx"

#include <map>

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

			using pending_streams_type		= std::map<FFprobe::stream::TYPE, size_t>;
			using stream_map_type			= std::map<FFprobe::stream::TYPE, std::map<unsigned short, Database::Data::film::stream>>;
			using stream_id					= std::pair<FFprobe::stream::TYPE, short>; // Not unsigned as can be -1 for all
			using group_file_info			= std::pair<std::list<std::filesystem::path>, std::list<std::filesystem::path>>; // First valid files, second invalid files (not having supported extensions)
			using film_group				= std::list<Database::Data::film>;

			bool 									run_initial_checks();
			Database::Data::film::priority			ask_priority();
			bool									ask_animation();
			FFprobe									get_film_data();
			pending_streams_type					initialize_pending_streams(const FFprobe&);
			stream_map_type							initialize_stream_map();
			void									display_stream_map(const FFprobe&, const stream_map_type&);
			std::optional<stream_id>				ask_stream_id(const FFprobe&, const pending_streams_type&);
			void									ask_stream(const FFprobe&, const stream_id&, stream_map_type&, pending_streams_type&);
			Database::Data::film					generate_film(const stream_map_type&, const Database::Data::film::priority&, const bool& animation);
			std::optional<unsigned int>				insert_film(const Database::Data::film&);
			#ifdef ENABLE_HEVC
			group_file_info							find_files_recursive();
			bool									ask_group_confirmation(const group_file_info&);
			Database::Data::film::group				insert_group();
			std::list<Database::Data::film::stream>	generate_default_streams_for_group(const bool& animation);
			film_group								generate_film_group(const group_file_info&, const Database::Data::film::group& group, const Database::Data::film::priority&, const bool& animation);
			bool									insert_film_group(const film_group&);
			#endif
			
			static void signal_handler(int);

			std::string m_buffer_str;
			int m_buffer_int;
			bool m_buffer_bool;
	};
}