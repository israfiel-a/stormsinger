set(ABYSSGUARD_FILE "Abyssguard.c")

add_executable(Stormsinger ${ABYSSGUARD_FILE})
add_dependencies(Stormsinger Chainbinder)
target_include_directories(Stormsinger PRIVATE "${CMAKE_SOURCE_DIR}/Chainbinder")
target_link_libraries(Stormsinger Chainbinder)
