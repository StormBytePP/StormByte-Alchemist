add_executable(StormByte-VideoConvert
	main.cxx
)
target_compile_features(StormByte-VideoConvert PUBLIC cxx_std_17)
target_link_libraries(StormByte-VideoConvert StormByte-VideoConvert-library)