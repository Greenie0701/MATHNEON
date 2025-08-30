// test_neon_add.c - Comprehensive test for NEON addition operations
#include "MN_dtype.h"
#include "MN_math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Test configuration
#define TEST_SIZE_SMALL 15    // Not divisible by 4 (tests remainder handling)
#define TEST_SIZE_LARGE 1000  // Divisible by 4 (tests main SIMD loop)
#define EPSILON 1e-6f         // Floating point comparison tolerance

// Color codes for test output
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

// Test result tracking
typedef struct {
    int passed;
    int failed;
    int total;
} test_stats_t;

// Utility functions
void print_test_header(const char* test_name) {
    printf(COLOR_BLUE "=== Testing %s ===" COLOR_RESET "\n", test_name);
}

void print_test_result(const char* test_name, int passed, test_stats_t* stats) {
    stats->total++;
    if (passed) {
        stats->passed++;
        printf(COLOR_GREEN "✓ %s PASSED" COLOR_RESET "\n", test_name);
    } else {
        stats->failed++;
        printf(COLOR_RED "✗ %s FAILED" COLOR_RESET "\n", test_name);
    }
}

// Float comparison with tolerance
int float_equal(float a, float b) {
    return fabs(a - b) < EPSILON;
}

// =============================================================================
// Test Functions for Scalar Arrays
// =============================================================================

int test_add_float_neon(test_stats_t* stats) {
    print_test_header("mn_add_float_neon");
    
    // Test both small (remainder) and large (aligned) sizes
    int sizes[] = {TEST_SIZE_SMALL, TEST_SIZE_LARGE};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int s = 0; s < num_sizes; s++) {
        int count = sizes[s];
        
        // Allocate aligned memory
        mn_float32_t* src1 = (mn_float32_t*)aligned_alloc(16, count * sizeof(mn_float32_t));
        mn_float32_t* src2 = (mn_float32_t*)aligned_alloc(16, count * sizeof(mn_float32_t));
        mn_float32_t* dst_neon = (mn_float32_t*)aligned_alloc(16, count * sizeof(mn_float32_t));
        mn_float32_t* dst_reference = (mn_float32_t*)aligned_alloc(16, count * sizeof(mn_float32_t));
        
        if (!src1 || !src2 || !dst_neon || !dst_reference) {
            printf("Memory allocation failed\n");
            return 0;
        }
        
        // Initialize test data
        for (int i = 0; i < count; i++) {
            src1[i] = (float)(i + 1) * 1.5f;
            src2[i] = (float)(i + 1) * 0.5f;
        }
        
        // Compute reference result using C
        if (mn_add_float_c(dst_reference, src1, src2, count) != MN_SUCCESS) {
            printf("C reference implementation failed\n");
            free(src1); free(src2); free(dst_neon); free(dst_reference);
            return 0;
        }
        
        // Compute NEON result
        if (mn_add_float_neon(dst_neon, src1, src2, count) != MN_SUCCESS) {
            printf("NEON implementation failed\n");
            free(src1); free(src2); free(dst_neon); free(dst_reference);
            return 0;
        }
        
        // Compare results
        int passed = 1;
        for (int i = 0; i < count; i++) {
            if (!float_equal(dst_neon[i], dst_reference[i])) {
                printf("Mismatch at index %d: NEON=%.6f, Reference=%.6f\n", 
                       i, dst_neon[i], dst_reference[i]);
                passed = 0;
                break;
            }
        }
        
        char test_name[100];
        snprintf(test_name, sizeof(test_name), "mn_add_float_neon (count=%d)", count);
        print_test_result(test_name, passed, stats);
        
        free(src1); free(src2); free(dst_neon); free(dst_reference);
    }
    
    return 1;
}

int test_add_int32_neon(test_stats_t* stats) {
    print_test_header("mn_add_int32_neon");
    
    int sizes[] = {TEST_SIZE_SMALL, TEST_SIZE_LARGE};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int s = 0; s < num_sizes; s++) {
        int count = sizes[s];
        
        mn_int32_t* src1 = (mn_int32_t*)aligned_alloc(16, count * sizeof(mn_int32_t));
        mn_int32_t* src2 = (mn_int32_t*)aligned_alloc(16, count * sizeof(mn_int32_t));
        mn_int32_t* dst_neon = (mn_int32_t*)aligned_alloc(16, count * sizeof(mn_int32_t));
        mn_int32_t* dst_reference = (mn_int32_t*)aligned_alloc(16, count * sizeof(mn_int32_t));
        
        if (!src1 || !src2 || !dst_neon || !dst_reference) {
            printf("Memory allocation failed\n");
            return 0;
        }
        
        // Initialize test data
        for (int i = 0; i < count; i++) {
            src1[i] = i + 1;
            src2[i] = (i + 1) * 2;
        }
        
        // Compute reference and NEON results
        mn_add_int32_c(dst_reference, src1, src2, count);
        mn_add_int32_neon(dst_neon, src1, src2, count);
        
        // Compare results
        int passed = 1;
        for (int i = 0; i < count; i++) {
            if (dst_neon[i] != dst_reference[i]) {
                printf("Mismatch at index %d: NEON=%d, Reference=%d\n", 
                       i, dst_neon[i], dst_reference[i]);
                passed = 0;
                break;
            }
        }
        
        char test_name[100];
        snprintf(test_name, sizeof(test_name), "mn_add_int32_neon (count=%d)", count);
        print_test_result(test_name, passed, stats);
        
        free(src1); free(src2); free(dst_neon); free(dst_reference);
    }
    
    return 1;
}

// =============================================================================
// Test Functions for Vector Types
// =============================================================================

int test_add_vec2f_neon(test_stats_t* stats) {
    print_test_header("mn_add_vec2f_neon");
    
    int count = 10; // Test 10 vec2f elements
    
    mn_vec2f_t* src1 = (mn_vec2f_t*)aligned_alloc(16, count * sizeof(mn_vec2f_t));
    mn_vec2f_t* src2 = (mn_vec2f_t*)aligned_alloc(16, count * sizeof(mn_vec2f_t));
    mn_vec2f_t* dst_neon = (mn_vec2f_t*)aligned_alloc(16, count * sizeof(mn_vec2f_t));
    mn_vec2f_t* dst_reference = (mn_vec2f_t*)aligned_alloc(16, count * sizeof(mn_vec2f_t));
    
    if (!src1 || !src2 || !dst_neon || !dst_reference) {
        printf("Memory allocation failed\n");
        return 0;
    }
    
    // Initialize test data
    for (int i = 0; i < count; i++) {
        src1[i].x = (float)(i + 1) * 1.1f;
        src1[i].y = (float)(i + 1) * 1.2f;
        src2[i].x = (float)(i + 1) * 0.9f;
        src2[i].y = (float)(i + 1) * 0.8f;
    }
    
    // Compute reference and NEON results
    mn_add_vec2f_c(dst_reference, src1, src2, count);
    mn_add_vec2f_neon(dst_neon, src1, src2, count);
    
    // Compare results
    int passed = 1;
    for (int i = 0; i < count; i++) {
        if (!float_equal(dst_neon[i].x, dst_reference[i].x) || 
            !float_equal(dst_neon[i].y, dst_reference[i].y)) {
            printf("Mismatch at vec2f[%d]: NEON=(%.6f,%.6f), Reference=(%.6f,%.6f)\n", 
                   i, dst_neon[i].x, dst_neon[i].y, dst_reference[i].x, dst_reference[i].y);
            passed = 0;
            break;
        }
    }
    
    print_test_result("mn_add_vec2f_neon", passed, stats);
    
    free(src1); free(src2); free(dst_neon); free(dst_reference);
    return passed;
}

int test_add_vec3f_neon(test_stats_t* stats) {
    print_test_header("mn_add_vec3f_neon");
    
    int count = 9; // Test 9 vec3f elements (not divisible by 4)
    
    mn_vec3f_t* src1 = (mn_vec3f_t*)aligned_alloc(16, count * sizeof(mn_vec3f_t));
    mn_vec3f_t* src2 = (mn_vec3f_t*)aligned_alloc(16, count * sizeof(mn_vec3f_t));
    mn_vec3f_t* dst_neon = (mn_vec3f_t*)aligned_alloc(16, count * sizeof(mn_vec3f_t));
    mn_vec3f_t* dst_reference = (mn_vec3f_t*)aligned_alloc(16, count * sizeof(mn_vec3f_t));
    
    if (!src1 || !src2 || !dst_neon || !dst_reference) {
        printf("Memory allocation failed\n");
        return 0;
    }
    
    // Initialize test data
    for (int i = 0; i < count; i++) {
        src1[i].x = (float)(i + 1) * 1.1f;
        src1[i].y = (float)(i + 1) * 1.2f;
        src1[i].z = (float)(i + 1) * 1.3f;
        src2[i].x = (float)(i + 1) * 0.7f;
        src2[i].y = (float)(i + 1) * 0.8f;
        src2[i].z = (float)(i + 1) * 0.9f;
    }
    
    // Compute reference and NEON results
    mn_add_vec3f_c(dst_reference, src1, src2, count);
    mn_add_vec3f_neon(dst_neon, src1, src2, count);
    
    // Compare results
    int passed = 1;
    for (int i = 0; i < count; i++) {
        if (!float_equal(dst_neon[i].x, dst_reference[i].x) || 
            !float_equal(dst_neon[i].y, dst_reference[i].y) ||
            !float_equal(dst_neon[i].z, dst_reference[i].z)) {
            printf("Mismatch at vec3f[%d]: NEON=(%.6f,%.6f,%.6f), Reference=(%.6f,%.6f,%.6f)\n", 
                   i, dst_neon[i].x, dst_neon[i].y, dst_neon[i].z,
                   dst_reference[i].x, dst_reference[i].y, dst_reference[i].z);
            passed = 0;
            break;
        }
    }
    
    print_test_result("mn_add_vec3f_neon", passed, stats);
    
    free(src1); free(src2); free(dst_neon); free(dst_reference);
    return passed;
}

int test_add_vec4f_neon(test_stats_t* stats) {
    print_test_header("mn_add_vec4f_neon");
    
    int count = 8; // Test 8 vec4f elements
    
    mn_vec4f_t* src1 = (mn_vec4f_t*)aligned_alloc(16, count * sizeof(mn_vec4f_t));
    mn_vec4f_t* src2 = (mn_vec4f_t*)aligned_alloc(16, count * sizeof(mn_vec4f_t));
    mn_vec4f_t* dst_neon = (mn_vec4f_t*)aligned_alloc(16, count * sizeof(mn_vec4f_t));
    mn_vec4f_t* dst_reference = (mn_vec4f_t*)aligned_alloc(16, count * sizeof(mn_vec4f_t));
    
    if (!src1 || !src2 || !dst_neon || !dst_reference) {
        printf("Memory allocation failed\n");
        return 0;
    }
    
    // Initialize test data
    for (int i = 0; i < count; i++) {
        src1[i].x = (float)(i + 1) * 1.1f;
        src1[i].y = (float)(i + 1) * 1.2f;
        src1[i].z = (float)(i + 1) * 1.3f;
        src1[i].w = (float)(i + 1) * 1.4f;
        src2[i].x = (float)(i + 1) * 0.6f;
        src2[i].y = (float)(i + 1) * 0.7f;
        src2[i].z = (float)(i + 1) * 0.8f;
        src2[i].w = (float)(i + 1) * 0.9f;
    }
    
    // Compute reference and NEON results
    mn_add_vec4f_c(dst_reference, src1, src2, count);
    mn_add_vec4f_neon(dst_neon, src1, src2, count);
    
    // Compare results
    int passed = 1;
    for (int i = 0; i < count; i++) {
        if (!float_equal(dst_neon[i].x, dst_reference[i].x) || 
            !float_equal(dst_neon[i].y, dst_reference[i].y) ||
            !float_equal(dst_neon[i].z, dst_reference[i].z) ||
            !float_equal(dst_neon[i].w, dst_reference[i].w)) {
            printf("Mismatch at vec4f[%d]\n", i);
            printf("  NEON: (%.6f,%.6f,%.6f,%.6f)\n", 
                   dst_neon[i].x, dst_neon[i].y, dst_neon[i].z, dst_neon[i].w);
            printf("  Ref:  (%.6f,%.6f,%.6f,%.6f)\n", 
                   dst_reference[i].x, dst_reference[i].y, dst_reference[i].z, dst_reference[i].w);
            passed = 0;
            break;
        }
    }
    
    print_test_result("mn_add_vec4f_neon", passed, stats);
    
    free(src1); free(src2); free(dst_neon); free(dst_reference);
    return passed;
}

// =============================================================================
// Performance Benchmark
// =============================================================================

void benchmark_add_operations() {
    printf(COLOR_BLUE "\n=== Performance Benchmark ===" COLOR_RESET "\n");
    
    const int benchmark_size = 1000000; // 1M elements
    const int iterations = 100;
    
    // Allocate benchmark data
    mn_float32_t* src1 = (mn_float32_t*)aligned_alloc(16, benchmark_size * sizeof(mn_float32_t));
    mn_float32_t* src2 = (mn_float32_t*)aligned_alloc(16, benchmark_size * sizeof(mn_float32_t));
    mn_float32_t* dst_c = (mn_float32_t*)aligned_alloc(16, benchmark_size * sizeof(mn_float32_t));
    mn_float32_t* dst_neon = (mn_float32_t*)aligned_alloc(16, benchmark_size * sizeof(mn_float32_t));
    
    if (!src1 || !src2 || !dst_c || !dst_neon) {
        printf("Benchmark memory allocation failed\n");
        return;
    }
    
    // Initialize data
    for (int i = 0; i < benchmark_size; i++) {
        src1[i] = (float)i * 0.1f;
        src2[i] = (float)i * 0.2f;
    }
    
    // Benchmark C implementation
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        mn_add_float_c(dst_c, src1, src2, benchmark_size);
    }
    clock_t end = clock();
    double time_c = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Benchmark NEON implementation
    start = clock();
    for (int i = 0; i < iterations; i++) {
        mn_add_float_neon(dst_neon, src1, src2, benchmark_size);
    }
    end = clock();
    double time_neon = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // Calculate speedup
    double speedup = time_c / time_neon;
    
    printf("C implementation:    %.6f seconds\n", time_c);
    printf("NEON implementation: %.6f seconds\n", time_neon);
    printf("Speedup:             %.2fx\n", speedup);
    
    free(src1); free(src2); free(dst_c); free(dst_neon);
}

// =============================================================================
// Edge Case Tests
// =============================================================================

int test_edge_cases(test_stats_t* stats) {
    print_test_header("Edge Cases");
    
    // Test with count = 1 (single element)
    {
        mn_float32_t src1 = 3.14f;
        mn_float32_t src2 = 2.86f;
        mn_float32_t dst_neon, dst_ref;
        
        mn_add_float_c(&dst_ref, &src1, &src2, 1);
        mn_add_float_neon(&dst_neon, &src1, &src2, 1);
        
        int passed = float_equal(dst_neon, dst_ref);
        print_test_result("Single element addition", passed, stats);
    }
    
    // Test with count = 0 (empty array)
    {
        mn_float32_t dummy = 0;
        mn_result_t result = mn_add_float_neon(&dummy, &dummy, &dummy, 0);
        int passed = (result == MN_SUCCESS);
        print_test_result("Zero count handling", passed, stats);
    }
    
    // Test with large numbers
    {
        mn_float32_t src1[] = {1e6f, -1e6f, 1e-6f, -1e-6f};
        mn_float32_t src2[] = {2e6f, -2e6f, 2e-6f, -2e-6f};
        mn_float32_t dst_neon[4], dst_ref[4];
        
        mn_add_float_c(dst_ref, src1, src2, 4);
        mn_add_float_neon(dst_neon, src1, src2, 4);
        
        int passed = 1;
        for (int i = 0; i < 4; i++) {
            if (!float_equal(dst_neon[i], dst_ref[i])) {
                passed = 0;
                break;
            }
        }
        print_test_result("Large/small number handling", passed, stats);
    }
    
    return 1;
}

// =============================================================================
// Main Test Runner
// =============================================================================

int main() {
    printf(COLOR_BLUE "==========================================\n");
    printf("     MN NEON Addition Operations Test\n");
    printf("==========================================" COLOR_RESET "\n\n");
    
    test_stats_t stats = {0, 0, 0};
    
    // Run all tests
    test_add_float_neon(&stats);
    test_add_int32_neon(&stats);
    test_add_vec2f_neon(&stats);
    test_add_vec3f_neon(&stats);
    test_add_vec4f_neon(&stats);
    test_edge_cases(&stats);
    
    // Print final results
    printf(COLOR_BLUE "\n=== Test Summary ===" COLOR_RESET "\n");
    printf("Total tests: %d\n", stats.total);
    printf(COLOR_GREEN "Passed: %d" COLOR_RESET "\n", stats.passed);
    if (stats.failed > 0) {
        printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", stats.failed);
    }
    
    if (stats.failed == 0) {
        printf(COLOR_GREEN "\n🎉 All tests passed! NEON implementation is working correctly.\n" COLOR_RESET);
        
        // Run performance benchmark if all tests pass
        benchmark_add_operations();
    } else {
        printf(COLOR_RED "\n❌ Some tests failed. Please check the NEON implementation.\n" COLOR_RESET);
        return 1;
    }
    
    return 0;
}
