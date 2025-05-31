############################################################################
## Stormsinger build file. This contains the CMake directives to build the
## project, start to finish, on every supported platform.
##
## Copyright (c) 2025 - the Stormsinger Project
## This document is under the GNU Affero General Public License v3.0. It
## can be modified and distributed (commercially or otherwise) freely, and
## can be used privately and within patents. No liability or warranty is
## guaranteed. However, on use, the user must state license and copyright,
## any changes made, and disclose the source of the document. For more
## information see the @file LICENSE.md file included with this
## distribution of the source code, or https://www.gnu.org/licenses/agpl.
############################################################################

cmake_minimum_required (VERSION 3.30 FATAL_ERROR)
project("Stormsinger" LANGUAGES C VERSION 0.0.0.3)

if(NOT DEFINED CMAKE_BUILD_TYPE)
	message(WARNING "No build type provided. Defaulting to release.")
	set(CMAKE_BUILD_TYPE "Release")
endif()

# Make our executable output into a directory we can plan for and predict.
# Otherwise, in the future if CMake or the build structure changes
# somewhat, we can dodge mystery linking issues. Also, it's prettier.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Stormsinger")

add_executable(Stormsinger "${CMAKE_SOURCE_DIR}/Source/Entry.c")
target_include_directories(Stormsinger PUBLIC "${CMAKE_SOURCE_DIR}/Include")

# Give version information to source files.
target_compile_definitions(Stormsinger PUBLIC 
    STORMSINGER_VERSION="${PROJECT_VERSION}"
	STORMSINGER_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	STORMSINGER_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	STORMSINGER_VERSION_PATCH=${PROJECT_VERSION_PATCH})

target_compile_options(Stormsinger PUBLIC -Wall -Wextra -Werror 
    -Wpedantic -Wno-gnu-zero-variadic-macro-arguments)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # Note that, in order for sanitize=pointer-compare to properly work
    # at runtime, one has to add detect_invalid_pointer_pairs=2 to their
    # ASAN_OPTIONS ENV variable.
    target_compile_options(Stormsinger PUBLIC -Og -g3 -ggdb 
        -fsanitize=address -fsanitize=pointer-compare -fsanitize=leak
        -fsanitize=pointer-subtract -fsanitize=undefined)
    target_link_options(Stormsinger PUBLIC -fsanitize=address 
        -fsanitize=undefined)

    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        target_compile_options(Stormsinger PUBLIC -fanalyzer)
    endif()
else()
    target_compile_options(Stormsinger PUBLIC -march=native 
        -mtune=native -Ofast -flto)
    target_link_options(Stormsinger PUBLIC -Ofast -flto)
endif()
