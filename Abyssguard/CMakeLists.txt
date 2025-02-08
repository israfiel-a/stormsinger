set(ABYSSGUARD_FILE "Abyssguard.cpp")

add_executable(Stormsinger ${ABYSSGUARD_FILE})
add_dependencies(Stormsinger Lightbleeder)
target_include_directories(Stormsinger PRIVATE "${CMAKE_SOURCE_DIR}/Lightbleeder/Include")
target_link_libraries(Stormsinger Lightbleeder)
