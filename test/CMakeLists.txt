add_executable(Myrddin
	main.cxx
)
target_compile_features(Myrddin PUBLIC cxx_std_17)
target_link_libraries(Myrddin Alchemy jsoncpp sqlite3)