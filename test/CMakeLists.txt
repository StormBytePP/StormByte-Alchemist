add_executable(StormByte-Myrddin
	main.cxx
)
target_compile_features(StormByte-Myrddin PUBLIC cxx_std_17)
target_link_libraries(StormByte-Myrddin StormByte-Alchemist)