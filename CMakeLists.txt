cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
project("Stormsinger" LANGUAGES C VERSION 0.1.0 DESCRIPTION 
	"Stormsinger is an infinite driving game set in the Leto universe")

if(NOT EXISTS CMAKE_BUILD_TYPE)
	message(WARNING "No build type provided. Defaulting to debug.")
	set(CMAKE_BUILD_TYPE "Debug")
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set(STORMSINGER_RELEASE true)
else()
	set(STORMSINGER_RELEASE false)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Stormsinger)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Chainbinder)
link_directories("${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

option(STORMSINGER_STRIP_LOG_METADATA "Strip things like the filename from logs." ${STORMSINGER_RELEASE})
option(STORMSINGER_DISABLE_LOGS "Disable all output logs." false)

# Damn you Microsoft. Damn you.
if(MSVC)
	add_compile_options(/std:clatest)
else()
	set(CMAKE_C_STANDARD_REQUIRED ON)
	set(CMAKE_C_STANDARD 23)
endif()

add_subdirectory("Chainbinder") # Pull in the Chainbinder engine.
add_subdirectory("Sunbringer")  # Pull in the Sunbringer asset library.
add_subdirectory("Abyssguard")  # Pull in the game's code.

# A list of the compiler options we'll apply to each target.
set(COMPILER_OPTIONS)
if(MSVC)
	list(APPEND COMPILER_OPTIONS /Wall /WX /external:W0 /external:anglebrackets /wd4711 /wd4710)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		list(APPEND COMPILER_OPTIONS /Od /Zi /Zo /EHa /EHr /fsanitize=address /fsanitize=fuzzer
			/fsanitize-coverage=edge /fsanitize-coverage=inline-8bit-counters
			/fsanitize-coverage=trace-cmp /fsanitize-coverage=trace-div)
	else()
		list(APPEND COMPILER_OPTIONS /O2 /fp:fast /GL /GS- /Gw /Qpar)
		add_link_options(/LTCG)
	endif()
else()
	list(APPEND COMPILER_OPTIONS -Wall -Wextra -Werror -Wpedantic -Wno-gnu-zero-variadic-macro-arguments)
	# TODO: Add more options when next on Linux machine.
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		list(APPEND COMPILER_OPTIONS -O0 -g)
	else()
		list(APPEND COMPILER_OPTIONS -O3)
	endif()
endif()

target_compile_options(Chainbinder PRIVATE ${COMPILER_OPTIONS})
target_compile_options(Sunbringer PRIVATE ${COMPILER_OPTIONS})
target_compile_options(Stormsinger PRIVATE ${COMPILER_OPTIONS})

target_compile_definitions(Chainbinder PRIVATE 
	"STRIP_LOG_METADATA=$<BOOL:${STORMSINGER_STRIP_LOG_METADATA}>" 
	"DISABLE_LOGS=$<BOOL:${STORMSINGER_DISABLE_LOGS}>")
