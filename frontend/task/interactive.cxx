#include "interactive.hxx"
#include "application.hxx"
#include "utils/input.hxx"
#include "utils/display.hxx"
#include "task/execute_ffprobe_video_color.hxx"
#include "task/execute_ffprobe_streams.hxx"

#include <iostream>
#include <boost/algorithm/string.hpp> // For string lowercase
#include <csignal>
#include <sys/wait.h>

using namespace StormByte::VideoConvert;

Task::Interactive::Interactive():Task::Base() {
	signal(SIGINT,	signal_handler);

	m_require_logger = false;
	m_require_database = true;
}

Task::Interactive& Task::Interactive::get_instance() {
	static Interactive instance;
	return instance;
}

bool Task::Interactive::run_initial_checks() {
	const Types::path_t full_path = *m_config->get_input_folder() / *m_config->get_interactive_parameter();

	if (!std::filesystem::exists(full_path)) {
		std::cerr << "File " << (std::filesystem::is_directory(full_path) ? "path " : "") << full_path << " does not exist" << std::endl;
		return false;
	}
	else if (m_database->is_film_in_database(*m_config->get_interactive_parameter())) {
		std::cerr << "Film " << *m_config->get_interactive_parameter() << " is already in database!" << std::endl;
		return false;
	}
	else if (std::filesystem::is_directory(full_path) && m_database->is_group_in_database(*m_config->get_interactive_parameter())) {
		std::cerr << "Film group (folder) " << *m_config->get_interactive_parameter() << " is already in database" << std::endl;
		return false;
	}
	else
		return true;
}

Types::optional_path_t Task::Interactive::ask_title() {
	Types::optional_path_t result;

	std::cout << "Type new film title, empty to not rename original file: ";
	std::getline(std::cin, m_buffer_str);

	if (!m_buffer_str.empty())
		result = m_buffer_str;

	return result;
}

Database::Data::film::priority Task::Interactive::ask_priority() {
	do {
		std::cout << "Which priority (default NORMAL)? LOW(0), NORMAL(1), HIGH(2), IMPORTANT(3): ";
		std::getline(std::cin, m_buffer_str);
	} while (m_buffer_str != "" && !Utils::Input::to_int_in_range(m_buffer_str, m_buffer_int, 0, 3, true));

	return static_cast<Database::Data::film::priority>(m_buffer_str == "" ? 1 : m_buffer_int);
}

bool Task::Interactive::ask_animation() {
	do {
		std::cout << "Is an animated movie? [(y)es/(n)o]: ";
		std::getline(std::cin, m_buffer_str);
	} while (!Utils::Input::in_yes_no(m_buffer_str, m_buffer_bool, true));

	return m_buffer_bool;
}

FFprobe Task::Interactive::get_film_data() {
	FFprobe probe;
	std::unique_ptr<Task::Execute> task;

	const Types::path_t full_path = *m_config->get_input_folder() / *m_config->get_interactive_parameter(); 
	task.reset(new Task::ExecuteFFprobeVideoColor(full_path));
	task->run(m_config);
	probe.initialize_video_color_data(task->get_output());
	task.reset(new Task::ExecuteFFprobeStreams(full_path));
	for (const auto i : { FFprobe::stream::VIDEO, FFprobe::stream::AUDIO, FFprobe::stream::SUBTITLE }) {
		dynamic_cast<Task::ExecuteFFprobeStreams&>(*task).set_mode(i);
		task->run(m_config);
		probe.initialize_stream_data(task->get_output(), i);
	}

	return probe;
}

void Task::Interactive::update_title_renamed(const FFprobe& film_data, const stream_map_t& stream_data, Types::optional_path_t& title) {
	if (title) {
		const auto resolution = film_data.get_resolution();
		std::string new_title = *title;
		if (resolution)
			new_title += " - m" + FFprobe::stream::RESOLUTION_STRING.at(*resolution);

		if (stream_data.at(FFprobe::stream::VIDEO).begin()->second.m_hdr)
			new_title += " HDR";
		title = new_title + ".mkv";
	}
}

Task::Interactive::pending_streams_t Task::Interactive::initialize_pending_streams(const FFprobe& probe) {
	return std::map<FFprobe::stream::TYPE, size_t> {
		{ FFprobe::stream::VIDEO,		probe.get_stream(FFprobe::stream::VIDEO).size() },
		{ FFprobe::stream::AUDIO,		probe.get_stream(FFprobe::stream::AUDIO).size() },
		{ FFprobe::stream::SUBTITLE,	probe.get_stream(FFprobe::stream::SUBTITLE).size() }
	};
}

Task::Interactive::stream_map_t Task::Interactive::initialize_stream_map() {
	return std::map<FFprobe::stream::TYPE, std::map<unsigned short, Database::Data::film::stream>> {
		{
			{ FFprobe::stream::VIDEO,		{} },
			{ FFprobe::stream::AUDIO,		{} },
			{ FFprobe::stream::SUBTITLE,	{} }
		}
	};
}

void Task::Interactive::display_stream_map(const FFprobe& probe, const stream_map_t& stream_map) {
	std::cout << "Film stream list:" << std::endl;
	for (FFprobe::stream::TYPE type: { FFprobe::stream::VIDEO, FFprobe::stream::AUDIO, FFprobe::stream::SUBTITLE }) {
		const auto& strm_probe = probe.get_stream(type);
		const auto& strm_map = stream_map.at(type);
		std::string line;
		for (size_t i = 0; i < strm_probe.size(); i++) {
			line = std::string(1, type) + ":" + std::to_string(i);
			line += " " + strm_probe[i].codec_name;

			if (strm_probe[i].language) {
				line += " (" + *strm_probe[i].language + ")";
			}
			line += " -> ";
			if (strm_map.contains(i)) {
				line += Database::Data::film::stream::codec_string.at(strm_map.at(i).m_codec);
			}
			else if (strm_map.contains(-1)) {
				line += Database::Data::film::stream::codec_string.at(strm_map.at(-1).m_codec);
			}
			else
				line += "(not selected)";

			std::cout << line << std::endl;
		}
	}
}

std::optional<Task::Interactive::stream_id_t> Task::Interactive::ask_stream_id(const FFprobe& probe, const pending_streams_t& pending_strms) {
	std::optional<Task::Interactive::stream_id_t> result;
	if (pending_strms.at(FFprobe::stream::VIDEO) == 0 && pending_strms.at(FFprobe::stream::AUDIO) == 0 && pending_strms.at(FFprobe::stream::SUBTITLE) == 0) {
		std::cout << "All streams have been selected" << std::endl << std::endl;
	}
	else {
		FFprobe::stream::TYPE selected_type;
		do {
			do {
				std::cout << "Which type to select? [(v)ideo/(a)udio/(s)ubtitle/(f)inish]: ";
				std::getline(std::cin, m_buffer_str);
			} while (!Utils::Input::in_options(m_buffer_str, { "v", "V", "a", "A", "s", "S", "f", "F" }, true));

			if (m_buffer_str == "f" || m_buffer_str == "F") {
				return std::optional<Task::Interactive::stream_id_t>();
			}
			else {
					selected_type = static_cast<FFprobe::stream::TYPE>(tolower(m_buffer_str[0]));
				if (pending_strms.at(selected_type) == 0) 
					std::cerr << "Selected type is already fully configured, select another type" << std::endl << std::endl;
			}
		} while (pending_strms.at(selected_type) == 0);

		do {
			std::cout << "Select stream ID: [-1, ";
			for (size_t i = 0; i < probe.get_stream(selected_type).size(); i++) {
				std::cout << i;
				if (i < probe.get_stream(selected_type).size() - 1) std::cout << ", ";
			}
			std::cout << "] (-1 means all for " << selected_type << "): ";
			std::getline(std::cin, m_buffer_str);
		} while (!Utils::Input::to_int_in_range(m_buffer_str, m_buffer_int, -1, probe.get_stream(selected_type).size() - 1, true));

		result = { selected_type, m_buffer_int };
	}
	return result;
}

void Task::Interactive::ask_stream([[maybe_unused]]const FFprobe& probe, const stream_id_t& strm_id, stream_map_t& strm_map, pending_streams_t& strm_pending) {
	std::list<int> options;
	if (strm_id.first == FFprobe::stream::VIDEO) {
		options = {
			Database::Data::film::stream::VIDEO_COPY,
			#ifdef ENABLE_HEVC
			Database::Data::film::stream::VIDEO_HEVC
			#endif
		};
		options.sort();
	}
	else if (strm_id.first == FFprobe::stream::AUDIO) {
		options = {
			Database::Data::film::stream::AUDIO_COPY,
			#ifdef ENABLE_AAC
			Database::Data::film::stream::AUDIO_AAC,
			#endif
			#ifdef ENABLE_FDKAAC
			Database::Data::film::stream::AUDIO_FDKAAC,
			#endif
			#ifdef ENABLE_AC3
			Database::Data::film::stream::AUDIO_AC3,
			#endif
			#ifdef ENABLE_EAC3
			Database::Data::film::stream::AUDIO_EAC3,
			#endif
			#ifdef ENABLE_OPUS
			Database::Data::film::stream::AUDIO_OPUS,
			#endif
		};
		options.sort();
	}
	else if (strm_id.first == FFprobe::stream::SUBTITLE) {
		options = {
			Database::Data::film::stream::SUBTITLE_COPY
		};
		options.sort();
	}
	
	std::cout << "Available codecs:" << std::endl;
	for (int i : options) {
		std::cout << i << ": " << Database::Data::film::stream::codec_string.at(static_cast<Database::Data::film::stream::codec>(i)) << std::endl;
	}

	do {
		std::cout << "Select desired codec: " << Utils::Display::list_to_string(options, "[", ", ", "]") << ": ";
		std::getline(std::cin, m_buffer_str);
	} while (!Utils::Input::to_int_positive(m_buffer_str, m_buffer_int) && !Utils::Input::in_options(m_buffer_int, options, true));

	Database::Data::film::stream stream;

	// Construct the stream
	stream.m_id = strm_id.second;
	stream.m_codec = static_cast<Database::Data::film::stream::codec>(m_buffer_int);

	// Final tunings depending on type
	if (strm_id.first == FFprobe::stream::VIDEO) {
		#ifdef ENABLE_HEVC
		if (probe.is_HDR_detected()) {
			std::cout << "HDR was detected!" << std::endl;
			stream.m_hdr = probe.get_HDR().data();
		}
		else if (probe.is_HDR_factible()) {
			do {
				std::cout << "HDR not found but is factible, put default HDR? [(y)es/(n)o]: ";
				std::getline(std::cin, m_buffer_str);
			} while (!Utils::Input::in_yes_no(m_buffer_str, m_buffer_bool, true));
			if (m_buffer_bool) {
				stream.m_hdr = probe.get_HDR().data();
			}
		}
		#endif
	}
	else if (strm_id.first == FFprobe::stream::AUDIO) {
		// Nothing yet
	}
	else if (strm_id.first == FFprobe::stream::SUBTITLE) {
		// Nothing yet
	}

	// Now we update our variables
	if (strm_id.second == -1)
		strm_pending.at(strm_id.first) = 0;
	else
		strm_pending.at(strm_id.first) = strm_pending.at(strm_id.first) - 1;

	strm_map.at(strm_id.first)[strm_id.second] = stream;
}

Database::Data::film Task::Interactive::generate_film(const stream_map_t& stream_map, const Database::Data::film::priority& priority, const Types::optional_path_t& title, const bool& animation) {
	Database::Data::film result;
	result.m_priority = priority;
	result.m_file = *m_config->get_interactive_parameter();
	result.m_title = title;
	std::list<Database::Data::film::stream> streams;

	// For FFmpeg map order matters so we do in order
	for (FFprobe::stream::TYPE type: { FFprobe::stream::VIDEO, FFprobe::stream::AUDIO, FFprobe::stream::SUBTITLE }) {
		for (auto it = stream_map.at(type).begin(); it != stream_map.at(type).end(); it++) {
			Database::Data::film::stream tmp_stream = it->second;
			if (tmp_stream.m_codec == Database::Data::film::stream::VIDEO_HEVC)
				tmp_stream.m_is_animation = animation;
			streams.push_back(std::move(tmp_stream));
		}
	}
	result.m_streams = std::move(streams);

	return result;
}

std::optional<unsigned int> Task::Interactive::insert_film(const Database::Data::film& film) {
	return m_database->insert_film(film);
}

#ifdef ENABLE_HEVC
Task::Interactive::group_file_info_t Task::Interactive::find_files_recursive() {
	const Types::path_t full_folder = *m_config->get_input_folder() / *m_config->get_interactive_parameter();

	std::list<Types::path_t> valid, invalid;

	for (std::filesystem::recursive_directory_iterator it(full_folder), end; it != end; ++it) {
		if (!is_directory(it->path())) {
			const std::string extension = it->path().extension();
			Types::path_t relative = std::filesystem::relative(it->path(), *m_config->get_input_folder());
			if (std::find(Application::SUPPORTED_MULTIMEDIA_EXTENSIONS.begin(), Application::SUPPORTED_MULTIMEDIA_EXTENSIONS.end(), extension) == Application::SUPPORTED_MULTIMEDIA_EXTENSIONS.end())
				invalid.push_back(relative);
			else
				valid.push_back(relative);
		}
	}

	return { valid, invalid };
}

bool Task::Interactive::ask_group_confirmation(const group_file_info_t& group_info) {
	bool result = true;

	if (group_info.first.empty()) {
		std::cerr 	<< "No valid files found in path "
					<< *m_config->get_interactive_parameter()
					<< " with accepted extensions "
					<< Utils::Display::list_to_string(Application::SUPPORTED_MULTIMEDIA_EXTENSIONS, "(", ", ", ")")
					<< std::endl;
		result = false;
	}
	else {
		std::cout << "Found " << group_info.first.size() << " film(s)" << std::endl;
		if (!group_info.second.empty()) {
			std::cout << "Warning: found " << group_info.second.size() << " invalid file(s) that will be ignored." << std::endl;
			for (Types::path_t file: group_info.second)
				std::cout << "\t* " << file.string() << std::endl;
		}
		do {
			std::cout << "Do you wish yo continue? [(y)es/(n)o]: ";
			std::getline(std::cin, m_buffer_str);
		} while(!Utils::Input::in_yes_no(m_buffer_str, m_buffer_bool, true));
		result = m_buffer_bool;
	}

	return result;
}

Database::Data::film::group Task::Interactive::insert_group() {
	return *m_database->insert_group(*m_config->get_interactive_parameter());
}

std::list<Database::Data::film::stream> Task::Interactive::generate_default_streams_for_group(const bool& animation) {
	Database::Data::film::stream video, audio, subtitle;

	video.m_id = 0;
	video.m_codec = Database::Data::film::stream::VIDEO_HEVC;
	video.m_is_animation = animation;
	
	audio.m_id = -1;
	audio.m_codec = Database::Data::film::stream::AUDIO_COPY;

	subtitle.m_id = -1;
	subtitle.m_codec = Database::Data::film::stream::SUBTITLE_COPY;

	return { video, audio, subtitle };
}

Task::Interactive::film_group_t Task::Interactive::generate_film_group_t(const group_file_info_t& film_group_t_info, const Database::Data::film::group& group, const Database::Data::film::priority& priority, const bool& animation) {
	film_group_t result;

	const std::list<Database::Data::film::stream> streams = generate_default_streams_for_group(animation);

	for (Types::path_t film_path: film_group_t_info.first) {
		Database::Data::film film;
		film.m_file = film_path;
		film.m_group = group;
		film.m_priority = priority;
		film.m_streams = streams;
		result.push_back(std::move(film));
	}

	return result;
}

bool Task::Interactive::insert_film_group_t(const film_group_t& film_group_t) {
	bool operation = m_database->insert_films(film_group_t);
	
	if (operation) {
		std::cout << "Inserted " << film_group_t.size() << " film(s) in database" << std::endl;
	}
	else {
		std::cerr << "There was an error inserting and therefore no films were added!" << std::endl;
	}

	return operation;
}
#endif

Task::STATUS Task::Interactive::run(Types::config_t config) noexcept {
	if (Base::run(config) == RUNNING) {
		Application::display_header();
		
		if (!run_initial_checks()) return HALT_ERROR;

		m_status = HALT_OK; // Unless something changes, this will return HALT_OK

		Types::optional_path_t title;
		// Title is only displayed when not in batch mode (path)
		if (!std::filesystem::is_directory(*m_config->get_input_folder() / *m_config->get_interactive_parameter()))
			title = ask_title();
		Database::Data::film::priority priority = ask_priority();
		bool animation = ask_animation();

		if (std::filesystem::is_directory(*m_config->get_input_folder() / *m_config->get_interactive_parameter())) {
			#ifdef ENABLE_HEVC
			group_file_info_t files = find_files_recursive();
			if (files.first.empty()) {
				m_status = HALT_ERROR;
			}
			if (ask_group_confirmation(files)) {
				Database::Data::film::group group = insert_group();
				if (!insert_film_group_t(
					generate_film_group_t(
						files,
						group,
						priority,
						animation
					)
				)) {
					m_status = HALT_ERROR;
				}
			}
			#else
			std::cerr << "Directory aditions are only available with HEVC support but it was not compiled in" << std::endl;
			return HALT_ERROR;
			#endif
		}
		else {
			Database::Data::film film;
			FFprobe film_data = get_film_data();

			auto pending_streams = initialize_pending_streams(film_data);
			auto stream_map = initialize_stream_map();
			
			bool continue_asking = true;
			do {
				display_stream_map(film_data, stream_map);
				std::optional<stream_id_t> strm_id = ask_stream_id(film_data, pending_streams);

				if (!strm_id) continue_asking = false;
				else {
					ask_stream(film_data, *strm_id, stream_map, pending_streams);
				}
			} while (continue_asking);

			update_title_renamed(film_data, stream_map, title);
			film = generate_film(stream_map, priority, title, animation);

			if (film.m_streams.empty()) {
				std::cerr << "There were no streams selected for film " + m_config->get_interactive_parameter()->string() + ", no changes were made to database" << std::endl;
				m_status = HALT_ERROR;
			}
			else {
				std::optional<unsigned int> film_id = insert_film(film);

				if (film_id) {
					std::cout << "Film " << *m_config->get_interactive_parameter() << " was inserted with ID " << *film_id << std::endl;
				}
				else {
					std::cerr << "Could NOT insert film!" << std::endl;
					m_status = HALT_ERROR;
				}
			}
		}
	}
	return m_status;
}

void Task::Interactive::signal_handler(int) {
	std::exit(0);
}
