if(WIN32)
	file(READ "default_windows.cfg" DEFAULT_CONFIG)
else()
	file(READ "default_linux.cfg" DEFAULT_CONFIG)
endif()
string(REGEX REPLACE "\n" "\\\\\n" DEFAULT_CONFIG "${DEFAULT_CONFIG}")
string(REGEX REPLACE "\"" "\\\\\"" DEFAULT_CONFIG "${DEFAULT_CONFIG}")

file(CONFIGURE OUTPUT ${CMAKE_BINARY_DIR}/generated/default_config.hxx CONTENT "#define ALCHEMY_DEFAULT_CONFIG \"\\
\\
${DEFAULT_CONFIG}\
\\
\"
")
