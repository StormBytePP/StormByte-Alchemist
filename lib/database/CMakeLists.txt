file(READ "create.sql" SQLITE_DATABASE_INIT)
string(REGEX REPLACE "\n+" " " SQLITE_DATABASE_INIT "${SQLITE_DATABASE_INIT}")

file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/database_create.hxx CONTENT "
	#include \"database/sqlite3.hxx\"
	const std::string Alchemist::Database::SQLite3::DATABASE_CREATE_SQL = \"${SQLITE_DATABASE_INIT}\";
")
