set(ABYSSGUARD_FILE "Abyssguard.cpp")
add_executable(Stormsinger ${ABYSSGUARD_FILE})
add_dependencies(Stormsinger Lightbleeder)
target_link_libraries(Stormsinger Lightbleeder)