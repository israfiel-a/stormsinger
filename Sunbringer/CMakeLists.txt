add_executable(Sunbringer "Sunbringer.c")

# file(COPY "Textures" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Sunbringer)

# These shaders are compiled into bytecode during the first run of the game, as they're
# being mushed into the archive.
# file(COPY "Shaders" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Sunbringer)