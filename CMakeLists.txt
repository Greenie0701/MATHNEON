cmake_minimum_required(VERSION 3.10)

project(MATHNEON C)

include(CheckCCompilerFlag)

# ===== Build Configurations =====
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Release or Debug" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# ===== Include Headers =====
include_directories(${PROJECT_SOURCE_DIR}/includes)

# ===== Detect NEON Support with try_compile =====
set(NEON_SUPPORTED FALSE)

try_compile(NEON_TEST_RESULT
    ${CMAKE_BINARY_DIR}/neon_check_build      
    ${PROJECT_SOURCE_DIR}/checks/neon_check.c 
    OUTPUT_VARIABLE NEON_TEST_OUTPUT
)

if(NEON_TEST_RESULT)
    set(NEON_SUPPORTED TRUE)
    message(STATUS "NEON check: SUCCESS → NEON enabled")
else()
    message(STATUS "NEON check: FAILED → NEON disabled")
    message(STATUS "Check output:\n${NEON_TEST_OUTPUT}")
endif()

# ===== Source Files =====
if(NEON_SUPPORTED)
    file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/src/*_neon.c
    )
else()
    file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/src/*.c
    )
endif()

# ===== Build Library =====
add_library(MATHNEON STATIC ${SOURCES})

# ===== Enable Testing =====
enable_testing()

add_executable(test_abs test/test_abs_neon.c)
target_link_libraries(test_abs PRIVATE MATHNEON)

add_test(NAME test_abs COMMAND test_abs)

# ===== Install Setup =====
install(TARGETS MATHNEON
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/includes/ DESTINATION include)
