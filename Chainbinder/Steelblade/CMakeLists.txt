cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)
project("Steelblade" LANGUAGES C VERSION 0.0.1.0 
    DESCRIPTION "A pure-C string wrapper for use in Chainbinder.")

if(NOT DEFINED CMAKE_BUILD_TYPE)
    message(WARNING "No build type provided. Defaulting to debug.")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# This disables flags that'll give clangd trouble, specifically -fanalyzer.
option(STEELBLADE_USING_CLANGD 
    "The clangd language server will be used post-compilation." OFF)

set(STEELBLADE_SOURCES "Steelblade.h" "Steelblade.c")
add_library(Steelblade STATIC ${STEELBLADE_SOURCES})

# Damn you Microsoft. Damn you.
if(MSVC)
    target_compile_options(Steelblade PRIVATE /std:clatest /Wall /WX /external:W0 /external:anglebrackets /wd4711 /wd4710 /wd4061 /wd5045)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(Steelblade PRIVATE /Od /Zi /Zo /EHa /EHr /fsanitize=address /fsanitize=fuzzer /fsanitize-coverage=edge /fsanitize-coverage=inline-8bit-counters /fsanitize-coverage=trace-cmp /fsanitize-coverage=trace-div)
    else()
        target_compile_options(Steelblade PRIVATE /O2 /fp:fast /GL /GS- /Gw /Qpar)
        target_link_options(Steelblade PRIVATE /LTCG)
    endif()
else()
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_STANDARD 23)

    target_compile_options(Steelblade PRIVATE -Wall -Wextra -Werror -Wpedantic -Wno-gnu-zero-variadic-macro-arguments)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        # Note that, in order for sanitize=pointer-compare to properly work
        # at runtime, one has to add detect_invalid_pointer_pairs=2 to their
        # ASAN_OPTIONS ENV variable.
        target_compile_options(Steelblade PRIVATE -Og -g3 -ggdb -fsanitize=address -fsanitize=pointer-compare -fsanitize=leak -fsanitize=pointer-subtract -fsanitize=undefined)
        target_link_options(Steelblade PRIVATE -fsanitize=address -fsanitize=undefined)

        if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND NOT 
            STEELBLADE_USING_CLANGD)
            target_compile_options(Steelblade PRIVATE -fanalyzer)
        endif()
    else()
        target_compile_options(Steelblade PRIVATE -Ofast -flto -march=native -mtune=native)
        target_link_options(Steelblade PRIVATE -Ofast -flto)
    endif()
endif()