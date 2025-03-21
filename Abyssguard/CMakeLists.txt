set(ABYSSGUARD_FILE "Abyssguard.c")

add_executable(Stormsinger ${ABYSSGUARD_FILE})
add_dependencies(Stormsinger Chainbinder)
target_include_directories(Stormsinger PRIVATE "${CMAKE_SOURCE_DIR}/Chainbinder")
target_link_libraries(Stormsinger Chainbinder)
target_compile_options(Stormsinger PRIVATE ${STORMSINGER_COMPILER_OPTIONS})

get_filename_component(filename ${ABYSSGUARD_FILE} NAME)
set_source_files_properties(${ABYSSGUARD_FILE} PROPERTIES COMPILE_DEFINITIONS FILENAME="${filename}")
