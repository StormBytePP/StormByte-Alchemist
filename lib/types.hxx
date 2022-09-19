#pragma once

#include <filesystem>
#include <optional>

/* Forward declarations */
namespace StormByte::VideoConvert::Configuration { class Base; }
namespace StormByte::VideoConvert::Utils { class Logger; }
namespace StormByte::VideoConvert::Database { class SQLite3; }

namespace StormByte::VideoConvert::Types {
	using path_t											= std::filesystem::path;
	using optional_path_t									= std::optional<path_t>;	
	using config_t											= std::shared_ptr<Configuration::Base>;
	using logger_t											= std::shared_ptr<Utils::Logger>;
	using database_t										= std::unique_ptr<Database::SQLite3>;
}
