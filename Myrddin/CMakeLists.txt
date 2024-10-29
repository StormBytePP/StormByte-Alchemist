add_executable(Myrddin
	main.cxx
)
target_compile_features(Myrddin PRIVATE cxx_std_20)
target_link_libraries(Myrddin Alchemy)