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
project("Stormsinger" LANGUAGES C VERSION 0.0.0.9)

if(NOT DEFINED CMAKE_BUILD_TYPE)
	message(WARNING "No build type provided. Defaulting to release.")
	set(CMAKE_BUILD_TYPE "Release")
endif()

include(CMakeDependentOption)
cmake_dependent_option(STORMSINGER_WAYLAND 
    "Use Wayland. If unselected, X11 is used." ON "UNIX;NOT APPLE" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Modules")
# Make our executable output into a directory we can plan for and predict.
# Otherwise, in the future if CMake or the build structure changes
# somewhat, we can dodge mystery linking issues. Also, it's prettier.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Stormsinger")

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(Stormsinger 
    "${CMAKE_SOURCE_DIR}/Source/Entrypoint.c"
    "${CMAKE_SOURCE_DIR}/Source/Vulkan.c" 
    "${CMAKE_SOURCE_DIR}/Source/Vulkan/Device.c" 
    "${CMAKE_SOURCE_DIR}/Source/Vulkan/Surface.c" 
    "${CMAKE_SOURCE_DIR}/Source/Vulkan/Surface/Wayland.c" 
    "${CMAKE_SOURCE_DIR}/Source/Window.c" 
    "${CMAKE_SOURCE_DIR}/Source/Window/Wayland.c"
    "${CMAKE_SOURCE_DIR}/Source/Window/Wayland/Registry.c"
    "${CMAKE_SOURCE_DIR}/Source/Window/Wayland/Shell.c"
    "${CMAKE_SOURCE_DIR}/Source/Window/Wayland/Compositor.c"
)
target_include_directories(Stormsinger PUBLIC "${CMAKE_SOURCE_DIR}/Include")

# Give version information to source files.
math(EXPR STORMSINGER_PACKED_VERSION "(${PROJECT_VERSION_MAJOR} << 22) | (${PROJECT_VERSION_MINOR} << 12) | ${PROJECT_VERSION_PATCH}")
target_compile_definitions(Stormsinger PUBLIC 
    STORMSINGER_VERSION=${STORMSINGER_PACKED_VERSION}
	STORMSINGER_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	STORMSINGER_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	STORMSINGER_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	STORMSINGER_VERSION_TWEAK=${PROJECT_VERSION_TWEAK})

target_compile_options(Stormsinger PUBLIC -Wall -Wextra -Werror 
    -Wpedantic -Wno-gnu-zero-variadic-macro-arguments)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
    set_target_properties(Stormsinger PROPERTIES EXPORT_COMPILE_COMMANDS ON)

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

find_package(Vulkan REQUIRED)
target_link_libraries(Stormsinger ${Vulkan_LIBRARIES})
target_include_directories(Stormsinger PUBLIC ${Vulkan_INCLUDE_DIRS})

if(STORMSINGER_WAYLAND)
    target_compile_definitions(Stormsinger PUBLIC STORMSINGER_WAYLAND)

    find_package(Wayland REQUIRED)
    target_link_libraries(Stormsinger ${Wayland_LIBRARIES})
    target_include_directories(Stormsinger PUBLIC ${Wayland_INCLUDE_DIRS})
    
    find_package(Scanner REQUIRED)
    ecm_add_wayland_client_protocol(Stormsinger PROTOCOL 
        "${CMAKE_SOURCE_DIR}/Modules/Protocols/xdg-shell.xml" BASENAME 
        xdg-shell PRIVATE_CODE)
    # The above function adds the header into the build directory. We need to
    # make sure we can wrangle said header.
    target_include_directories(Stormsinger PUBLIC "${CMAKE_BINARY_DIR}")
endif()
