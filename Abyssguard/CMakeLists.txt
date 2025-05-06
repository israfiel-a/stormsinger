############################################################################
## Stormsinger game implementation sub-build module.
## Copyright (c) 2025 Israfil Argos
## This source code is under the AGPLv3.0. For information on what that 
## entails, see the LICENSE.md file that should have beem provided alongside 
## this source code, or https://gnu.org/licenses/agpl-3.0.
############################################################################

############################################################################
## Source File Collection
############################################################################

# No globs here because there aren't as many files as in Chainbinder.
set(ABYSSGUARD_SOURCES "Abyssguard.c")

############################################################################
## Target Creation
############################################################################

add_executable(Stormsinger ${ABYSSGUARD_SOURCES})
add_dependencies(Stormsinger Chainbinder)
target_link_libraries(Stormsinger Chainbinder)
file(COPY "Chainbinder.cfg" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

############################################################################
## Compilation Options
############################################################################

target_compile_options(Stormsinger PRIVATE ${STORMSINGER_COMPILER_OPTIONS})
foreach(file ${ABYSSGUARD_SOURCES})
	get_filename_component(filename ${ABYSSGUARD_SOURCES} NAME)
	set_source_files_properties(${ABYSSGUARD_SOURCES} PROPERTIES 
		COMPILE_DEFINITIONS FILENAME="${filename}")
endforeach()
