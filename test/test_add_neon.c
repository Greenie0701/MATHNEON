// test_neon_add_fixed.c - Fixed version with proper memory management
#include "MN_dtype.h"
#include "MN_math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifdef _MSC_VER
    #include <malloc.h>
    #define aligned_alloc_custom(alignment, size) _aligned_malloc(size, alignment)
    #define aligned_free_custom(ptr) _aligned_free(ptr)
#else
    #include <stdlib.h>
    #define aligned_alloc_custom(alignment, size) aligned_alloc(alignment, size)
    #define aligned_free_custom(ptr) free(ptr)
#endif

// Test configuration
#define TEST_SIZE_SMALL 15
#define TEST_SIZE_LARGE 1000
#define EPSILON 1e-6f

// Color codes for test output
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

typedef struct {
    int passed;
    int failed;
    int total;
} test_stats_t;

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

int float_equal(float a, float b) {
    return fabs(a - b) < EPSILON;
}

// Safe memory allocation with error checking
void* safe_aligned_alloc(size_t alignment, size_t size) {
    void* ptr = aligned_alloc_custom(alignment, size);
    if (!ptr) {
        printf("ERROR: Memory allocation failed for %zu bytes\n", size);
        exit(1);
    }
    // Initialize to zero to avoid using uninitialized memory
    memset(ptr, 0, size);
    return ptr;
}

// Cleanup helper that handles multiple pointers
void cleanup_memory(void** ptrs, int count) {
    for (int i = 0; i < count; i++) {
        if (ptrs[i]) {
            aligned_free_custom(ptrs[i]);
            ptrs[i] = NULL;
        }
    }
}

int test_add_float_neon_safe(test_stats_t* stats) {
    print_test_header("mn_add_float_neon (safe version)");
    
    int sizes[] = {TEST_SIZE_SMALL, TEST_SIZE_LARGE};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int s = 0; s < num_sizes; s++) {
        int count = sizes[s];
        printf("Testing with count = %d\n", count);
        
        // Allocate extra space to detect buffer overruns
        size_t alloc_size = (count + 4) * sizeof(mn_float32_t);
        
        mn_float32_t* src1 = (mn_float32_t*)safe_aligned_alloc(16, alloc_size);
        mn_float32_t* src2 = (mn_float32_t*)safe_aligned_alloc(16, alloc_size);
        mn_float32_t* dst_neon = (mn_float32_t*)safe_aligned_alloc(16, alloc_size);
        mn_float32_t* dst_reference = (mn_float32_t*)safe_aligned_alloc(16, alloc_size);
        
        void* ptrs[] = {src1, src2, dst_neon, dst_reference};
        
        // Initialize test data with known values
        for (int i = 0; i < count; i++) {
            src1[i] = (float)(i + 1) * 1.5f;
            src2[i] = (float)(i + 1) * 0.5f;
        }
        
        // Add canary values after the data to detect overwrites
        for (int i = count; i < count + 4; i++) {
            src1[i] = -999.0f;
            src2[i] = -999.0f;
            dst_neon[i] = -999.0f;
            dst_reference[i] = -999.0f;
        }
        
        printf("Computing reference result...\n");
        mn_result_t result_ref = mn_add_float_c(dst_reference, src1, src2, count);
        if (result_ref != MN_SUCCESS) {
            printf("ERROR: C reference implementation failed with code %d\n", result_ref);
            cleanup_memory(ptrs, 4);
            continue;
        }
        
        printf("Computing NEON result...\n");
        mn_result_t result_neon = mn_add_float_neon(dst_neon, src1, src2, count);
        if (result_neon != MN_SUCCESS) {
            printf("ERROR: NEON implementation failed with code %d\n", result_neon);
            cleanup_memory(ptrs, 4);
            continue;
        }
        
        // Check canary values first
        int canary_ok = 1;
        for (int i = count; i < count + 4; i++) {
            if (dst_neon[i] != -999.0f || dst_reference[i] != -999.0f) {
                printf("ERROR: Buffer overrun detected at index %d\n", i);
                canary_ok = 0;
            }
        }
        
        if (!canary_ok) {
            cleanup_memory(ptrs, 4);
            continue;
        }
        
        // Compare results
        int passed = 1;
        for (int i = 0; i < count; i++) {
            if (!float_equal(dst_neon[i], dst_reference[i])) {
                printf("Mismatch at index %d: NEON=%.6f, Reference=%.6f, diff=%.8f\n", 
                       i, dst_neon[i], dst_reference[i], fabs(dst_neon[i] - dst_reference[i]));
                passed = 0;
                break;
            }
        }
        
        char test_name[100];
        snprintf(test_name, sizeof(test_name), "mn_add_float_neon (count=%d)", count);
        print_test_result(test_name, passed, stats);
        
        cleanup_memory(ptrs, 4);
    }
    
    return 1;
}

// Simple test with minimal operations
int test_simple_add(test_stats_t* stats) {
    print_test_header("Simple Addition Test");
    
    const int count = 4; // Exactly one SIMD register worth
    
    mn_float32_t src1[8] = {1.0f, 2.0f, 3.0f, 4.0f, 0, 0, 0, 0};
    mn_float32_t src2[8] = {0.5f, 1.5f, 2.5f, 3.5f, 0, 0, 0, 0};
    mn_float32_t dst_neon[8] = {0};
    mn_float32_t dst_ref[8] = {0};
    
    printf("Input validation:\n");
    printf("src1: [%.1f, %.1f, %.1f, %.1f]\n", src1[0], src1[1], src1[2], src1[3]);
    printf("src2: [%.1f, %.1f, %.1f, %.1f]\n", src2[0], src2[1], src2[2], src2[3]);
    
    // Test C implementation
    mn_result_t result_c = mn_add_float_c(dst_ref, src1, src2, count);
    printf("C result code: %d\n", result_c);
    if (result_c == MN_SUCCESS) {
        printf("C result: [%.1f, %.1f, %.1f, %.1f]\n", 
               dst_ref[0], dst_ref[1], dst_ref[2], dst_ref[3]);
    }
    
    // Test NEON implementation
    printf("Calling NEON implementation...\n");
    mn_result_t result_neon = mn_add_float_neon(dst_neon, src1, src2, count);
    printf("NEON result code: %d\n", result_neon);
    
    if (result_neon != MN_SUCCESS) {
        print_test_result("Simple NEON addition", 0, stats);
        return 0;
    }
    
    printf("NEON result: [%.1f, %.1f, %.1f, %.1f]\n", 
           dst_neon[0], dst_neon[1], dst_neon[2], dst_neon[3]);
    
    // Compare
    int passed = 1;
    for (int i = 0; i < count; i++) {
        if (!float_equal(dst_neon[i], dst_ref[i])) {
            printf("Mismatch at index %d: NEON=%.6f, Reference=%.6f\n", 
                   i, dst_neon[i], dst_ref[i]);
            passed = 0;
        }
    }
    
    print_test_result("Simple NEON addition", passed, stats);
    return passed;
}

// Test null pointer handling
int test_null_pointers(test_stats_t* stats) {
    print_test_header("Null Pointer Tests");
    
    mn_float32_t dummy[4] = {1, 2, 3, 4};
    
    // Test various null pointer scenarios
    mn_result_t result1 = mn_add_float_neon(NULL, dummy, dummy, 4);
    mn_result_t result2 = mn_add_float_neon(dummy, NULL, dummy, 4);
    mn_result_t result3 = mn_add_float_neon(dummy, dummy, NULL, 4);
    
    int passed = (result1 != MN_SUCCESS && result2 != MN_SUCCESS && result3 != MN_SUCCESS);
    print_test_result("Null pointer handling", passed, stats);
    
    return passed;
}

int main() {
    printf(COLOR_BLUE "==========================================\n");
    printf("     MN NEON Addition Operations Test\n");
    printf("     (Debug Version)\n");
    printf("==========================================" COLOR_RESET "\n\n");
    
    test_stats_t stats = {0, 0, 0};
    
    // Start with simple tests
    printf("Starting with basic tests...\n\n");
    
    test_null_pointers(&stats);
    test_simple_add(&stats);
    
    // Only continue with complex tests if simple ones pass
    if (stats.failed == 0) {
        printf("\nBasic tests passed, continuing with comprehensive tests...\n\n");
        test_add_float_neon_safe(&stats);
    }
    
    // Print final results
    printf(COLOR_BLUE "\n=== Test Summary ===" COLOR_RESET "\n");
    printf("Total tests: %d\n", stats.total);
    printf(COLOR_GREEN "Passed: %d" COLOR_RESET "\n", stats.passed);
    if (stats.failed > 0) {
        printf(COLOR_RED "Failed: %d" COLOR_RESET "\n", stats.failed);
    }
    
    if (stats.failed == 0) {
        printf(COLOR_GREEN "\n🎉 All tests passed!\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "\n❌ Some tests failed.\n" COLOR_RESET);
        return 1;
    }
    
    return 0;
}
