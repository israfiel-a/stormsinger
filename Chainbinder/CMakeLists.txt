file(GLOB CHAINBINDER_SOURCES "Source/*.c" "Include/*.h" "Source/Vulkan/*.c" 
	"Include/Vulkan/*.h")
file(GLOB CHAINBINDER_HEADER "Chainbinder.h")

add_library(Chainbinder STATIC ${CHAINBINDER_SOURCES} ${CHAINBINDER_HEADERS})

find_package(Vulkan REQUIRED)

include(FetchContent)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
	FetchContent_MakeAvailable(glfw)
endif()

add_dependencies(Chainbinder glfw)
target_include_directories(Chainbinder PUBLIC "${glfw_SOURCE_DIR}/include" 
    "${Vulkan_INCLUDE_DIRS}" "./")
target_include_directories(Chainbinder PRIVATE "Include")

target_link_libraries(Chainbinder PUBLIC glfw3 Vulkan::Vulkan)
if(UNIX)
	find_package(X11 REQUIRED)
	target_link_libraries(Chainbinder PUBLIC rt dl m ${X11_LIBRARIES})
endif()

foreach(file ${CHAINBINDER_SOURCES} ${CHAINBINDER_HEADER})
    get_filename_component(filename ${file} NAME)
    set_source_files_properties(${file} PROPERTIES COMPILE_DEFINITIONS FILENAME="${filename}")
endforeach()
