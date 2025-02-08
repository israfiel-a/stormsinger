add_executable(Sunbringer "Sunbringer.cpp")

if(MSVC)
	target_compile_options(Sunbringer PRIVATE /Wall)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(Sunbringer PRIVATE /Od)
	else()
		target_compile_options(Sunbringer PRIVATE /O2)
	endif()
else()
	target_compile_options(Sunbringer PRIVATE -Wall -Wextra -Werror -Wpedantic)
	# TODO: Add more options when next on Linux machine.
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(Sunbringer PRIVATE -O0 -g)
	else()
		target_compile_options(Sunbringer PRIVATE -O3)
	endif()
endif()

# file(COPY "Textures" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Sunbringer)

# These shaders are compiled into bytecode during the first run of the game, as they're
# being mushed into the archive.
# file(COPY "Shaders" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Sunbringer)