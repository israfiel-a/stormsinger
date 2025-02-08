cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
project("Stormsinger" LANGUAGES CXX VERSION 0.1.0 DESCRIPTION 
	"Stormsinger is an infinite driving game set in the Leto universe")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Stormsinger)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lightbleeder)
link_directories("${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("Lightbleeder") # Pull in the Lightbleeder engine.
add_subdirectory("Sunbringer")   # Pull in the Sunbringer asset library.
add_subdirectory("Abyssguard")   # Pull in the game's code.

# A list of the compiler options we'll apply to each target.
set(COMPILER_OPTIONS)
if(MSVC)
	list(APPEND COMPILER_OPTIONS /Wall /WX /external:W0 /external:anglebrackets)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		list(APPEND COMPILER_OPTIONS /Od /Zi /Zo /EHa /EHr /fsanitize=address /fsanitize=fuzzer
			/fsanitize-coverage=edge /fsanitize-coverage=inline-8bit-counters
			/fsanitize-coverage=trace-cmp /fsanitize-coverage=trace-div)
	else()
		list(APPEND COMPILER_OPTIONS /O2 /fp:fast /GL /GS- /Gw /Qpar)
	endif()
else()
	list(APPEND COMPILER_OPTIONS -Wall -Wextra -Werror -Wpedantic)
	# TODO: Add more options when next on Linux machine.
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		list(APPEND COMPILER_OPTIONS -O0 -g)
	else()
		list(APPEND COMPILER_OPTIONS -O3)
	endif()
endif()

target_compile_options(Lightbleeder PRIVATE ${COMPILER_OPTIONS})
target_compile_options(Sunbringer PRIVATE ${COMPILER_OPTIONS})
target_compile_options(Stormsinger PRIVATE ${COMPILER_OPTIONS})
