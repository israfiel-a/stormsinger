find_package(Vulkan REQUIRED COMPONENTS glslc)

add_executable(Sunbringer "Sunbringer.c" "Sunbringer.h")
target_compile_options(Sunbringer PRIVATE ${STORMSINGER_COMPILER_OPTIONS})
target_compile_definitions(Sunbringer PRIVATE "GLSL=\"${Vulkan_GLSLC_EXECUTABLE}\"")
target_include_directories(Sunbringer PUBLIC "${CMAKE_SOURCE_DIR}/Chainbinder")
target_link_libraries(Sunbringer Chainbinder)
add_dependencies(Sunbringer Chainbinder)

# file(COPY "Textures" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Sunbringer)

# These shaders are compiled into bytecode during the first run of the game, as they're
# being mushed into the archive.
file(COPY "Shaders" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")