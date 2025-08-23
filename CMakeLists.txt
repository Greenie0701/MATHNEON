cmake_minimum_required(VERSION 3.10)

project(MATHNEON C)

include_directories(${PROJECT_SOURCE_DIR}/includes)

set(SOURCES
    src/abs/MN_abs.c
)

add_library(MATHNEON STATIC ${SOURCES})
