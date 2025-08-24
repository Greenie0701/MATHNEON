cmake_minimum_required(VERSION 3.10)

project(MATHNEON C)

#Includes necessary headers for compiling sources
include_directories(${PROJECT_SOURCE_DIR}/includes)

#Recursively grab source files for compiling MATHNEON
file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.c
)

#Generate test executable to validate implementations 
add_executable(test_abs test/test_abs_neon.c)
target_link_libraries(test_abs PRIVATE MATHNEON)

add_library(MATHNEON STATIC ${SOURCES})
