cmake_minimum_required(VERSION 3.10)

project(MATHNEON C)

include(CheckCCompilerFlag)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Release or Debug" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

include_directories(${PROJECT_SOURCE_DIR}/includes)

set(NEON_SUPPORTED FALSE)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    check_c_compiler_flag("-mfpu=neon" COMPILER_SUPPORTS_NEON)
    if(COMPILER_SUPPORTS_NEON)
        set(NEON_SUPPORTED TRUE)
        add_compile_options(-mfpu=neon)
        message(STATUS "NEON support detected: Enabled")
    else()
        message(STATUS "NEON not supported by compiler")
    endif()
else()
    message(STATUS "Non-ARM architecture, NEON disabled")
endif()

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

if(NEON_SUPPORTED)
    list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/abs/MN_abs_neon.c)
else()
    list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/abs/MN_abs.c)
endif()

add_library(MATHNEON STATIC ${SOURCES})

enable_testing()

add_executable(test_abs test/test_abs_neon.c)
target_link_libraries(test_abs PRIVATE MATHNEON)

add_test(NAME test_abs COMMAND test_abs)

install(TARGETS MATHNEON
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/includes/ DESTINATION include)
