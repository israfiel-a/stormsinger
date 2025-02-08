cmake_minimum_required (VERSION 3.8 FATAL_ERROR)
project("Stormsinger" LANGUAGES CXX VERSION 0.1.0 DESCRIPTION 
	"Stormsinger is an infinite driving game set in the Leto universe")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Stormsinger)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lightbleeder)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

if(MSVC)
	add_compile_options(/Wall)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		add_compile_options(/Od)
	else()
		add_compile_options(/O2)
	endif()
else()
	add_compile_options(-Wall -Wextra -Werror -Wpedantic)
	# TODO: Add more options when next on Linux machine.
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		add_compile_options(-O0 -g)
	else()
		add_compile_options(-O3)
	endif()
endif()

add_subdirectory("Lightbleeder") # Pull in the Lightbleeder engine.
add_subdirectory("Sunbringer")   # Pull in the Sunbringer asset library.
add_subdirectory("Abyssguard")   # Pull in the game's code.
