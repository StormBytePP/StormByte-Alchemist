if (WITH_SYSTEM_CONFIG++)
	find_package (Config++ REQUIRED)
else()
	# make_directory(${CMAKE_CURRENT_LIST_DIR}/build)
	# add_custom_target(Config++ ALL
	# 	cmake -B${CMAKE_CURRENT_LIST_DIR}/build -H${CMAKE_CURRENT_LIST_DIR}/src -GNinja -DCMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}" -DBUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=ON -DBUILD_TESTS=OFF
	# 	COMMAND ninja -C${CMAKE_CURRENT_LIST_DIR}/build install
	# 	#BYPRODUCTS "${CMAKE_BINARY_DIR}/bin/thirdparty/hdr10plus_tool"
	# )
	include(CheckSymbolExists)
	set(BUILD_SHARED_LIBS ON)
	set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
	add_subdirectory(src/lib)
endif()
