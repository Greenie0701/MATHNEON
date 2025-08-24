cmake_minimum_required(VERSION 3.10)

project(MATHNEON C)

include_directories(${PROJECT_SOURCE_DIR}/includes)

file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.c
)

add_library(MATHNEON STATIC ${SOURCES})
