############################################################################
## Stormbringer root CMake build file.
## Copyright (c) 2025 Israfil Argos
## This source code is under the AGPLv3.0. For information on what that 
## entails, see the LICENSE.md file that should have beem provided alongside 
## this source code, or https://gnu.org/licenses/agpl-3.0.
############################################################################

cmake_minimum_required (VERSION 3.30 FATAL_ERROR)
project("Stormsinger" LANGUAGES C VERSION 0.1.1 DESCRIPTION 
	"Stormsinger is an infinite driving game set in the Leto universe")

############################################################################
## Compilation Mode Settings
############################################################################

if(NOT DEFINED CMAKE_BUILD_TYPE)
	message(WARNING "No build type provided. Defaulting to debug.")
	set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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

option(STORMSINGER_USE_X11 "Use X11 over Wayland for windowing." OFF)

# This disables flags that'll give clangd trouble, specifically -fanalyzer.
option(STORMSINGER_USING_CLANGD 
    "The clangd language server will be used post-compilation." OFF)

option(STORMSINGER_DISABLE_VALIDATION_LAYERS "Don't use Vulkan validation layers.")
set(STORMSINGER_DISABLE_VALIDATION_LAYERS ${STORMSINGER_RELEASE} CACHE BOOL 
	"Don't use Vulkan validation layers." FORCE)

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
	STORMSINGER_DISABLE_LOGS=$<BOOL:${STORMSINGER_DISABLE_LOGS}>
    STORMSINGER_VALIDATION_LAYERS=$<BOOL:${STORMSINGER_VALIDATION_LAYERS}>)

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

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        # Note that, in order for sanitize=pointer-compare to properly work
        # at runtime, one has to add detect_invalid_pointer_pairs=2 to their
        # ASAN_OPTIONS ENV variable.
		list(APPEND STORMSINGER_COMPILER_OPTIONS -Og -g3 -ggdb
            -fsanitize=address -fsanitize=pointer-compare -fsanitize=leak
            -fsanitize=pointer-subtract -fsanitize=undefined)
        add_link_options(-fsanitize=address -fsanitize=undefined)

        if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND NOT 
            STORMSINGER_USING_CLANGD)
            list(APPEND STORMSINGER_COMPILER_OPTIONS -fanalyzer)
        endif()
	else()
		list(APPEND STORMSINGER_COMPILER_OPTIONS -Ofast -flto)
        add_link_options(-Ofast -flto)
	endif()
endif()

############################################################################
## Subdirectory Wrangling
############################################################################

add_subdirectory("Chainbinder") # Pull in the Chainbinder engine.
add_subdirectory("Sunbringer")  # Pull in the Sunbringer asset library.
add_subdirectory("Abyssguard")  # Pull in the game's code.
