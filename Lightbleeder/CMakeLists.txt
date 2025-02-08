set(LIGHTBLEEDER_SOURCES "Source/Lightbleeder.cpp" "Source/Window.cpp")
set(LIGHTBLEEDER_HEADERS "Include/Lightbleeder.hpp" "Source/Window.cpp")

add_library(Lightbleeder STATIC ${LIGHTBLEEDER_SOURCES} ${LIGHTBLEEDER_HEADERS})
add_dependencies(Lightbleeder glfw)
target_include_directories(Lightbleeder PRIVATE "Include")
target_link_libraries(Lightbleeder PUBLIC glfw3)
