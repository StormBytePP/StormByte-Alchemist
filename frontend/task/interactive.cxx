#include "interactive.hxx"
#include "application.hxx"
#include "utils/input.hxx"

#include <iostream>
#include <boost/algorithm/string.hpp> // For string lowercase
#include <csignal>

using namespace StormByte::VideoConvert;

Task::Interactive::Interactive():Task::Base() {
	signal(SIGINT,	signal_handler);
}

Task::Interactive& Task::Interactive::get_instance() {
	static Interactive instance;
	return instance;
}

Task::STATUS Task::Interactive::run(std::shared_ptr<Configuration> config) noexcept {
	if (Base::run(config) == RUNNING) {
		Application::display_header();
		const std::filesystem::path full_path = *m_config->get_input_folder() / *m_config->get_interactive_parameter();

		if (!std::filesystem::exists(full_path)) {
			std::cerr << "File " << (std::filesystem::is_directory(full_path) ? "path " : "") << full_path << " does not exist" << std::endl;
			return HALT_ERROR;
		}
		else if (m_database->is_film_in_database(*m_config->get_interactive_parameter())) {
			std::cerr << "Film " << *m_config->get_interactive_parameter() << " is already in database!" << std::endl;
			return HALT_ERROR;
		}
		else if (std::filesystem::is_directory(full_path) && m_database->is_group_in_database(*m_config->get_interactive_parameter())) {
			std::cerr << "Film group (folder) " << *m_config->get_interactive_parameter() << " is already in database" << std::endl;
			return HALT_ERROR;
		}
		
		/* Query required data */
		auto films = std::move(ask_film_data());
		if (!films) return HALT_ERROR;
		auto streams = std::move(ask_streams());

		// Now we put the streams into all films
		for (auto film = films->begin(); film != films->end(); film++)
			film->m_streams = streams;

		if (add_films_to_database(std::move(*films)))
			m_status = HALT_OK;
		else
			m_status = HALT_ERROR;
	}

	return m_status;
}

std::optional<std::list<Database::Data::film>> Task::Interactive::ask_film_data() const {
	std::string buffer_str;
	int buffer_int;
	std::list<Database::Data::film> films;
	std::list<std::filesystem::path> unsupported_films;
	Database::Data::film film;
	do {
		std::cout << "Which priority (default NORMAL)? LOW(0), NORMAL(1), HIGH(2), IMPORTANT(3): ";
		std::getline(std::cin, buffer_str);
	} while (buffer_str != "" && !Utils::Input::to_int_in_range(buffer_str, buffer_int, 0, 3, true));
	film.m_priority = static_cast<Database::Data::film::priority>((buffer_str == "") ? 1 : buffer_int);

	// Now we look if a single film was specified or if it was a folder
	const std::filesystem::path full_path = *m_config->get_input_folder() / *m_config->get_interactive_parameter();
	const std::filesystem::path input_folder = *m_config->get_input_folder();
	if (std::filesystem::is_directory(full_path)) {
		film.m_group = m_database->insert_group(*m_config->get_interactive_parameter());

		// Look for all supported films in directory
		for (std::filesystem::recursive_directory_iterator i(full_path), end; i != end; ++i) 
			if (!std::filesystem::is_directory(i->path())) {
				std::string extension = boost::to_lower_copy(i->path().extension().string());
				if (std::find(Application::SUPPORTED_MULTIMEDIA_EXTENSIONS.begin(), Application::SUPPORTED_MULTIMEDIA_EXTENSIONS.end(), extension) != Application::SUPPORTED_MULTIMEDIA_EXTENSIONS.end()) {
					film.m_file = std::filesystem::relative(i->path(), input_folder);
					films.push_back(film);
				}
				else {
					unsupported_films.push_back(std::filesystem::relative(i->path(), input_folder));
				}
			}
	}
	else {
		// Single file
		film.m_file = *m_config->get_interactive_parameter();
		films.push_back(film);
	}

	if (!unsupported_films.empty()) {
		std::cout << "Found " << std::to_string(unsupported_films.size()) << " unsupported films:\n";
		for (auto it = unsupported_films.begin(); it != unsupported_films.end(); it++)
			std::cout << "\t* " << (*it) << "\n";
		std::cout << std::endl;
		do {
			std::cout << "Do you wish to continue? [y/n]: ";
			std::getline(std::cin, buffer_str);
		} while(!Utils::Input::in_options(buffer_str, { "y", "Y", "n", "N" }));
		if (buffer_str == "n" || buffer_str == "N") return std::optional<std::list<Database::Data::film>>();
	}

	return films;
}

std::list<Database::Data::film::stream> Task::Interactive::ask_streams() {
	std::map<char, bool> continue_asking {
		{ 'v', true },
		{ 'a', true },
		{ 's', true }
	};
	std::list<Database::Data::film::stream> streams;
	bool add_new_stream, continue_asking_any;

	do {
		std::string buffer_str;		
		do {
			std::cout << "Select stream type; video(v), audio(a) or subtitles(s): ";
			std::getline(std::cin, buffer_str);
		} while (!Utils::Input::in_options(buffer_str, { "v", "V", "a", "A", "s", "S" }, true));
		char codec_type = tolower(buffer_str[0]);

		if (!continue_asking[codec_type]) {
			std::cerr << "Selected stream type " << codec_type << " has been already fully defined" << std::endl;
		}
		else {
			auto stream = std::move(ask_stream(codec_type));
			continue_asking[codec_type] = stream.m_id >= 0; // If negative, means all streams have been covered
			streams.push_back(std::move(stream));
			continue_asking_any = continue_asking['v'] || continue_asking['a'] || continue_asking['s'];

			if (continue_asking_any)
				do {
					buffer_str = "";
					std::cout << "Add another stream? [y/n]: ";
					std::getline(std::cin, buffer_str);
				} while(!Utils::Input::in_options(buffer_str, { "y", "Y", "n", "N" }));
			else
				std::cout << "There are no more streams to add" << std::endl;

			add_new_stream = buffer_str == "y" || buffer_str == "Y";
		}
	} while(add_new_stream && continue_asking_any);

	return streams;
}

Database::Data::film::stream Task::Interactive::ask_stream(const char& codec_type) const {
	Database::Data::film::stream stream;
	std::string buffer_str;
	int buffer_int;

	do {
		std::cout << "Input stream(" << codec_type << ") FFmpeg ID (-1 to select all streams for type " << codec_type << "): ";
		std::getline(std::cin, buffer_str);
	} while(!Utils::Input::to_int_minimum(buffer_str, buffer_int, -1, true));
	stream.m_id = buffer_int;

	if (codec_type == 'v') {
		do {
			std::cout << "Select video codec:" << std::endl;
			std::cout << "\tcopy(" << Database::Data::film::stream::VIDEO_COPY << ")" << std::endl;
			#ifdef ENABLE_HEVC
			std::cout << "\tHEVC(" << Database::Data::film::stream::VIDEO_HEVC << ")" << std::endl;
			#endif
			std::cout << "Which codec to use?: ";
			std::getline(std::cin, buffer_str);
		} while (!Utils::Input::to_int(buffer_str, buffer_int, true) || !Utils::Input::in_options(
			buffer_str,
			{
				#ifdef ENABLE_HEVC
				std::to_string(Database::Data::film::stream::VIDEO_HEVC),
				#endif
				std::to_string(Database::Data::film::stream::VIDEO_COPY)
			},
			true
		));
		stream.m_codec = static_cast<Database::Data::film::stream::codec>(buffer_int);

		// Only certain codecs supports animation, TODO: Make it better
		if (stream.m_codec == Database::Data::film::stream::VIDEO_HEVC) {
			do {
				buffer_str = "";
				std::cout << "Is an animated movie? [y/n]: ";
				std::getline(std::cin, buffer_str);
			} while (!Utils::Input::in_options(buffer_str, { "y", "Y", "n", "N" }));
			if (buffer_str == "y" || buffer_str == "Y")
				stream.m_is_animation = true;
		}
	
		#ifdef ENABLE_HEVC
		if (stream.m_codec == Database::Data::film::stream::VIDEO_HEVC) {
			do {
				std::cout << "Does it have HDR? [y/n]: ";
				std::getline(std::cin, buffer_str);
			} while(!Utils::Input::in_options(
				buffer_str,
				{ "y", "Y", "n", "N" }
			));
			if (buffer_str == "y" || buffer_str == "Y")
				stream.m_hdr.emplace(ask_stream_hdr());
		}
		#endif
	}
	else if (codec_type == 'a') {
		do {
			std::cout << "Select audio codec:" << std::endl;
			#ifdef ENABLE_AAC
			std::cout << "\tAAC(" << Database::Data::film::stream::AUDIO_AAC << ")" << std::endl;
			#endif
			#ifdef ENABLE_FDKAAC
			std::cout << "\tFDKAAC(" << Database::Data::film::stream::AUDIO_FDKAAC << ")" << std::endl;
			#endif
			#ifdef ENABLE_AC3
			std::cout << "\tAC-3(" << Database::Data::film::stream::AUDIO_AC3 << ")" << std::endl;
			#endif
			#ifdef ENABLE_EAC3
			std::cout << "\tE-AC3(" << Database::Data::film::stream::AUDIO_EAC3 << ")" << std::endl;
			#endif
			#ifdef ENABLE_OPUS
			std::cout << "\tOpus(" << Database::Data::film::stream::AUDIO_OPUS << ")" << std::endl;
			#endif
			std::cout << "\tcopy(" << Database::Data::film::stream::AUDIO_COPY << ")" << std::endl;
			std::cout << "Which codec to use?: ";
			std::getline(std::cin, buffer_str);
		} while (!Utils::Input::to_int(buffer_str, buffer_int, true) || !Utils::Input::in_options(
			buffer_str,
			{
				#ifdef ENABLE_AAC
				std::to_string(Database::Data::film::stream::AUDIO_AAC),
				#endif
				#ifdef ENABLE_AC3
				std::to_string(Database::Data::film::stream::AUDIO_AC3),
				#endif
				#ifdef ENABLE_EAC3
				std::to_string(Database::Data::film::stream::AUDIO_EAC3),
				#endif
				#ifdef ENABLE_OPUS
				std::to_string(Database::Data::film::stream::AUDIO_OPUS),
				#endif
				#ifdef ENABLE_FDKAAC
				std::to_string(Database::Data::film::stream::AUDIO_FDKAAC),
				#endif
				std::to_string(Database::Data::film::stream::AUDIO_COPY),
			},
			true
		));
		stream.m_codec = static_cast<Database::Data::film::stream::codec>(buffer_int);
	}
	else {
		std::cout << "Subtitles have only copy codec so it is being autoselected" << std::endl;
		stream.m_codec = Database::Data::film::stream::SUBTITLE_COPY;
	}

	return stream;
}

bool Task::Interactive::add_films_to_database(const std::list<Database::Data::film>& films) {
	if (m_database->insert_films(films)) {
		std::cout << "Inserted " << std::to_string(films.size()) + " film(s) in database" << std::endl;
		return true;
	}
	else {
		std::cerr << "Some films failed to be inserted, therefore none were inserted" << std::endl;
		return false;
	}
}

#ifdef ENABLE_HEVC
Database::Data::film::stream::hdr Task::Interactive::ask_stream_hdr() const {
	Database::Data::film::stream::hdr HDR;
	std::string buffer_str;
	int buffer_int;

	std::cout << "Input HDR parameters (leave empty to use default value):" << std::endl;

	do {
		buffer_str = "";
		std::cout << "red x (" << Stream::Video::HEVC::HDR::DEFAULT_REDX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.red_x = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_REDX : buffer_int;

	do {
		buffer_str = "";
		std::cout << "red y (" << Stream::Video::HEVC::HDR::DEFAULT_REDY << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.red_y = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_REDY : buffer_int;

	do {
		buffer_str = "";
		std::cout << "green x (" << Stream::Video::HEVC::HDR::DEFAULT_GREENX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.green_x = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_GREENX : buffer_int;

	do {
		buffer_str = "";
		std::cout << "green y (" << Stream::Video::HEVC::HDR::DEFAULT_GREENY << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.green_y = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_GREENY : buffer_int;

	do {
		buffer_str = "";
		std::cout << "blue x (" << Stream::Video::HEVC::HDR::DEFAULT_BLUEX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.blue_x = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_BLUEX : buffer_int;

	do {
		buffer_str = "";
		std::cout << "blue y (" << Stream::Video::HEVC::HDR::DEFAULT_BLUEY << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.blue_y = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_BLUEY : buffer_int;

	do {
		buffer_str = "";
		std::cout << "white point x (" << Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.white_point_x = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTX : buffer_int;

	do {
		buffer_str = "";
		std::cout << "white point y (" << Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTY << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.white_point_y = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_WHITEPOINTY : buffer_int;

	do {
		buffer_str = "";
		std::cout << "luminance min (" << Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMIN << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.luminance_min = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMIN : buffer_int;

	do {
		buffer_str = "";
		std::cout << "luminance max (" << Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMAX << "): ";
		std::getline(std::cin, buffer_str);
	} while(buffer_str != "" && !Utils::Input::to_int_positive(buffer_str, buffer_int, true));
	HDR.luminance_max = (buffer_str == "") ? Stream::Video::HEVC::HDR::DEFAULT_LUMINANCEMAX : buffer_int;

	do {
		buffer_str = "";
		std::cout << "Does it have light level data? [y/n]: ";
		std::getline(std::cin, buffer_str);
	} while(!Utils::Input::in_options(buffer_str, { "y", "Y", "n", "N" }, true));

	if (buffer_str == "y" || buffer_str == "Y") {
		int ll_content, ll_max;
		do {
			buffer_str = "";
			std::cout << "light level content: ";
			std::getline(std::cin, buffer_str);
		} while(!Utils::Input::to_int_positive(buffer_str, ll_content, true));

		do {
			buffer_str = "";
			std::cout << "light level average: ";
			std::getline(std::cin, buffer_str);
		} while(!Utils::Input::to_int_positive(buffer_str, ll_max, true));

		HDR.light_level = std::make_pair(ll_content, ll_max);
	}

	return HDR;
}
#endif

void Task::Interactive::signal_handler(int) {
	std::exit(0);
}
