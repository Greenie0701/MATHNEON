#TO DO: Find a way to add dispatcher for NEON
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
# Always include C fallbacks - explicit file list instead of glob
set(SOURCES_C
    ${PROJECT_SOURCE_DIR}/src/abs/MN_abs.c
    ${PROJECT_SOURCE_DIR}/src/abs/MN_add.c
    # Add other C implementation files here as you create them
)

if(NEON_SUPPORTED)
    set(SOURCES_NEON
        ${PROJECT_SOURCE_DIR}/src/abs/MN_abs_neon.c
        ${PROJECT_SOURCE_DIR}/src/add/MN_add_neon.c
    )
    set(SOURCES ${SOURCES_C} ${SOURCES_NEON})
else()
    set(SOURCES ${SOURCES_C})
endif()

# Print what files are being compiled for debugging
message(STATUS "C sources: ${SOURCES_C}")
if(NEON_SUPPORTED)
    message(STATUS "NEON sources: ${SOURCES_NEON}")
endif()

# ===== Build Library =====
add_library(MATHNEON STATIC ${SOURCES})

# ===== Enable Testing =====
enable_testing()
add_executable(test_abs test/test_abs_neon.c)
add_executable(test_abs test/test_add_neon.c)
target_link_libraries(test_abs PRIVATE MATHNEON)
add_test(NAME test_abs COMMAND test_abs)

# ===== Install Setup =====
install(TARGETS MATHNEON
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/includes/ DESTINATION include)
