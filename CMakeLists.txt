############################################################################
## Stormbringer root CMake build file.
## Copyright (c) 2025 Israfil Argos
## This source code is under the AGPLv3.0. For information on what that 
## entails, see the LICENSE.md file that should have beem provided alongside 
## this source code, or https://gnu.org/licenses/agpl-3.0.
############################################################################

cmake_minimum_required (VERSION 3.30 FATAL_ERROR)
project("Stormsinger" LANGUAGES C VERSION 0.1.0 DESCRIPTION 
	"Stormsinger is an infinite driving game set in the Leto universe")

############################################################################
## Compilation Mode Settings
############################################################################

if(NOT DEFINED CMAKE_BUILD_TYPE)
	message(WARNING "No build type provided. Defaulting to debug.")
	set(CMAKE_BUILD_TYPE "Debug")
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set(STORMSINGER_RELEASE ON)
else()
	set(STORMSINGER_RELEASE OFF)
endif()

############################################################################
## Project Configuration Options
############################################################################

option(STORMSINGER_STRIP_LOG_METADATA 
	"Strip things like the filename from logs.")
set(STORMSINGER_STRIP_LOG_METADATA ${STORMSINGER_RELEASE} CACHE BOOL 
	"Strip things like the filename from logs." FORCE)

option(STORMSINGER_DISABLE_LOGS "Disable all output logs.")
set(STORMSINGER_DISABLE_LOGS ${STORMSINGER_RELEASE} CACHE BOOL 
	"Disable all output logs." FORCE)

############################################################################
## Output Directories
############################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Stormsinger)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Chainbinder)

############################################################################
## Commandline Flags
############################################################################

link_directories("${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

add_compile_definitions(STORMSINGER_VERSION="${PROJECT_VERSION}"
	STORMSINGER_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	STORMSINGER_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	STORMSINGER_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	STORMSINGER_STRIP_LOG_METADATA=$<BOOL:${STORMSINGER_STRIP_LOG_METADATA}> 
	STORMSINGER_DISABLE_LOGS=$<BOOL:${STORMSINGER_DISABLE_LOGS}>)

# Damn you Microsoft. Damn you.
if(MSVC)
	add_compile_options(/std:clatest)
else()
	set(CMAKE_C_STANDARD_REQUIRED ON)
	set(CMAKE_C_STANDARD 23)
endif()

# A list of the compiler options we'll apply to each target.
set(STORMSINGER_COMPILER_OPTIONS)
if(MSVC)
	list(APPEND STORMSINGER_COMPILER_OPTIONS /Wall /WX /external:W0 
		/external:anglebrackets /wd4711 /wd4710)

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		list(APPEND STORMSINGER_COMPILER_OPTIONS /Od /Zi /Zo /EHa /EHr 
			/fsanitize=address /fsanitize=fuzzer /fsanitize-coverage=edge 
			/fsanitize-coverage=inline-8bit-counters 
			/fsanitize-coverage=trace-cmp /fsanitize-coverage=trace-div)
	else()
		list(APPEND STORMSINGER_COMPILER_OPTIONS /O2 /fp:fast /GL /GS- 
			/Gw /Qpar)
		add_link_options(/LTCG)
	endif()
else()
	list(APPEND STORMSINGER_COMPILER_OPTIONS -Wall -Wextra -Werror 
		-Wpedantic -Wno-gnu-zero-variadic-macro-arguments)

	# TODO: Add more options when next on Linux machine.
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		list(APPEND STORMSINGER_COMPILER_OPTIONS -O0 -g)
	else()
		list(APPEND STORMSINGER_COMPILER_OPTIONS -O3)
	endif()
endif()

############################################################################
## Subdirectory Wrangling
############################################################################

add_subdirectory("Chainbinder") # Pull in the Chainbinder engine.
add_subdirectory("Sunbringer")  # Pull in the Sunbringer asset library.
add_subdirectory("Abyssguard")  # Pull in the game's code.
