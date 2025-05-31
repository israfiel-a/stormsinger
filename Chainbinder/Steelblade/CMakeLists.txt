set(STEELBLADE_SOURCES "Steelblade.h" "Steelblade.c")
add_library(Steelblade STATIC ${STEELBLADE_SOURCES})
target_compile_options(Steelblade PRIVATE ${STORMSINGER_COMPILER_OPTIONS})