set(LIGHTBLEEDER_SOURCES "Source/Lightbleeder.cpp" "Source/Window.cpp")
set(LIGHTBLEEDER_HEADERS "Include/Lightbleeder.hpp" "Source/Window.cpp")

add_library(Lightbleeder STATIC ${LIGHTBLEEDER_SOURCES} ${LIGHTBLEEDER_HEADERS})

find_package(Vulkan REQUIRED)

include(FetchContent)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.3.4)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
	FetchContent_MakeAvailable(glfw)
endif()

add_dependencies(Lightbleeder glfw)
target_include_directories(Lightbleeder PUBLIC "${glfw_SOURCE_DIR}/include" 
    "${Vulkan_INCLUDE_DIRS}" "Include")
target_link_libraries(Lightbleeder PUBLIC glfw3)
message(STATUS ${GLFW_PKG_LIBS})
if(UNIX)
	find_package(X11 REQUIRED)
	target_link_libraries(Lightbleeder PUBLIC rt dl m ${X11_LIBRARIES})
endif()
