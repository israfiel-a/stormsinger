cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
project("Stormsinger" LANGUAGES CXX VERSION 0.1.0 DESCRIPTION 
	"Stormsinger is an infinite driving game set in the Leto universe")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Stormsinger)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lightbleeder)
link_directories("${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.3.4)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
	FetchContent_Populate(glfw)
    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
	add_subdirectory("${glfw_SOURCE_DIR}" "${glfw_BINARY_DIR}" EXCLUDE_FROM_ALL)
endif()
include_directories("${glfw_SOURCE_DIR}/include")

add_subdirectory("Lightbleeder") # Pull in the Lightbleeder engine.
add_subdirectory("Sunbringer")   # Pull in the Sunbringer asset library.
add_subdirectory("Abyssguard")   # Pull in the game's code.
