############################################################################
## Stormsinger engine sub-build module.
## Copyright (c) 2025 Israfil Argos
## This source code is under the AGPLv3.0. For information on what that 
## entails, see the LICENSE.md file that should have beem provided alongside 
## this source code, or https://gnu.org/licenses/agpl-3.0.
############################################################################

############################################################################
## Source File Collection
############################################################################

set(CHAINBINDER_PUBLIC_INTERFACE "Chainbinder.h")
# Globs aren't best practice, but to be honest I'm lazy.
file(GLOB CHAINBINDER_SOURCES "Source/*.c" "Include/*.h" "Source/Vulkan/*.c" 
	"Source/Config/*.c" "Include/Vulkan/*.h" "Include/Config/*.h")

############################################################################
## Dependency Wrangling
############################################################################

include(FetchContent)
find_package(Vulkan REQUIRED)
if(UNIX AND STORMSINGER_USE_X11)
	find_package(X11 REQUIRED)
endif()

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git 
	GIT_TAG 3.4)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
	FetchContent_MakeAvailable(glfw)
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
	set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL 
		"Build the GLFW example programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    if(UNIX AND STORMSINGER_USE_X11)
        set(GLFW_BUILD_WAYLAND OFF CACHE INTERNAL "Build support for Wayland")
        set(GLFW_BUILD_X11 ON CACHE INTERNAL "Build support for X11")
    else()    
        set(GLFW_BUILD_WAYLAND ON CACHE INTERNAL "Build support for Wayland")
        set(GLFW_BUILD_X11 OFF CACHE INTERNAL "Build support for X11")
    endif()
endif()

############################################################################
## Target Creation
############################################################################

# The reason this library is static is that the space benefits only apply
# until the first run of the game, during which the Sunbringer executable
# is destroyed. It is more performant to keep this inserted directly into
# the executable.
add_library(Chainbinder STATIC ${CHAINBINDER_PUBLIC_INTERFACE} 
	${CHAINBINDER_SOURCES} ${CHAINBINDER_HEADERS})
add_dependencies(Chainbinder glfw)

target_include_directories(Chainbinder PUBLIC "${glfw_SOURCE_DIR}/include" 
    "${Vulkan_INCLUDE_DIRS}" "./" "Include")
target_link_libraries(Chainbinder PUBLIC glfw3 Vulkan::Vulkan)
if(UNIX)
	target_link_libraries(Chainbinder PUBLIC rt dl m)
    if(STORMSINGER_USE_X11)
        target_link_libraries(${X11_LIBRARIES})
    endif()
endif()

############################################################################
## Compilation Options
############################################################################

target_compile_options(Chainbinder PRIVATE ${STORMSINGER_COMPILER_OPTIONS})
foreach(file ${CHAINBINDER_SOURCES})
    get_filename_component(filename ${file} NAME)
    set_source_files_properties(${file} PROPERTIES COMPILE_DEFINITIONS 
		FILENAME="${filename}")
endforeach()
