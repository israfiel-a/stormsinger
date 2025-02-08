set(ABYSSGUARD_FILE "Abyssguard.cpp")

add_executable(Stormsinger ${ABYSSGUARD_FILE})

if(MSVC)
	target_compile_options(Stormsinger PRIVATE /Wall)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(Stormsinger PRIVATE /Od)
	else()
		target_compile_options(Stormsinger PRIVATE /O2)
	endif()
else()
	target_compile_options(Stormsinger PRIVATE -Wall -Wextra -Werror -Wpedantic)
	# TODO: Add more options when next on Linux machine.
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(Stormsinger PRIVATE -O0 -g)
	else()
		target_compile_options(Stormsinger PRIVATE -O3)
	endif()
endif()

add_dependencies(Stormsinger Lightbleeder)
target_include_directories(Stormsinger PRIVATE "${CMAKE_SOURCE_DIR}/Lightbleeder/Include")
target_link_libraries(Stormsinger Lightbleeder)
