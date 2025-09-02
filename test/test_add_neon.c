#include <stdio.h>
#include <stdlib.h>
#include "../includes/MN_dtype.h"
#include "../includes/MN_macro.h"
#include "../includes/MN_math.h"

int main(void)
{
    int count = 16;

    // Allocate memory for addition tests (need two source arrays)
    float* src1_f = (float*)malloc(sizeof(float) * count);
    float* src2_f = (float*)malloc(sizeof(float) * count);
    float* dst_f  = (float*)malloc(sizeof(float) * count);
    float* ref_f  = (float*)malloc(sizeof(float) * count);

    int* src1_i = (int*)malloc(sizeof(int) * count);
    int* src2_i = (int*)malloc(sizeof(int) * count);
    int* dst_i  = (int*)malloc(sizeof(int) * count);
    int* ref_i  = (int*)malloc(sizeof(int) * count);

    mn_vec2f_t* src1_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* src2_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* dst_v2f  = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* ref_v2f  = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);

    mn_vec2i_t* src1_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* src2_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* dst_v2i  = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* ref_v2i  = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);

    mn_vec3f_t* src1_v3f = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);
    mn_vec3f_t* src2_v3f = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);
    mn_vec3f_t* dst_v3f  = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);
    mn_vec3f_t* ref_v3f  = (mn_vec3f_t*)malloc(sizeof(mn_vec3f_t) * count);

    mn_vec3i_t* src1_v3i = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);
    mn_vec3i_t* src2_v3i = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);
    mn_vec3i_t* dst_v3i  = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);
    mn_vec3i_t* ref_v3i  = (mn_vec3i_t*)malloc(sizeof(mn_vec3i_t) * count);

    mn_vec4f_t* src1_v4f = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);
    mn_vec4f_t* src2_v4f = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);
    mn_vec4f_t* dst_v4f  = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);
    mn_vec4f_t* ref_v4f  = (mn_vec4f_t*)malloc(sizeof(mn_vec4f_t) * count);

    mn_vec4i_t* src1_v4i = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);
    mn_vec4i_t* src2_v4i = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);
    mn_vec4i_t* dst_v4i  = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);
    mn_vec4i_t* ref_v4i  = (mn_vec4i_t*)malloc(sizeof(mn_vec4i_t) * count);

    // Check all allocations
    if (!src1_f || !src2_f || !dst_f || !ref_f || 
        !src1_i || !src2_i || !dst_i || !ref_i ||
        !src1_v2f || !src2_v2f || !dst_v2f || !ref_v2f || 
        !src1_v2i || !src2_v2i || !dst_v2i || !ref_v2i ||
        !src1_v3f || !src2_v3f || !dst_v3f || !ref_v3f || 
        !src1_v3i || !src2_v3i || !dst_v3i || !ref_v3i ||
        !src1_v4f || !src2_v4f || !dst_v4f || !ref_v4f || 
        !src1_v4i || !src2_v4i || !dst_v4i || !ref_v4i)
    {
        fprintf(stderr, "malloc failed!\n");
        return 1;
    }

    // ==== Fill inputs ====
    printf("Initializing test data...\n");
    for (int i = 0; i < count; i++)
    {
        // Simple test values for addition
        src1_f[i] = (float)(i + 1);
        src2_f[i] = (float)(i + 1) * 0.5f;

        src1_i[i] = i + 1;
        src2_i[i] = (i + 1) * 2;

        src1_v2f[i].x = (float)(i + 1);
        src1_v2f[i].y = (float)(i + 1) * 1.1f;
        src2_v2f[i].x = (float)(i + 1) * 0.5f;
        src2_v2f[i].y = (float)(i + 1) * 0.6f;

        src1_v2i[i].x = i + 1;
        src1_v2i[i].y = (i + 1) * 2;
        src2_v2i[i].x = i + 10;
        src2_v2i[i].y = (i + 1) * 3;

        src1_v3f[i].x = (float)(i + 1);
        src1_v3f[i].y = (float)(i + 1) * 1.1f;
        src1_v3f[i].z = (float)(i + 1) * 1.2f;
        src2_v3f[i].x = (float)(i + 1) * 0.5f;
        src2_v3f[i].y = (float)(i + 1) * 0.6f;
        src2_v3f[i].z = (float)(i + 1) * 0.7f;

        src1_v3i[i].x = i + 1;
        src1_v3i[i].y = (i + 1) * 2;
        src1_v3i[i].z = (i + 1) * 3;
        src2_v3i[i].x = i + 10;
        src2_v3i[i].y = (i + 1) * 4;
        src2_v3i[i].z = (i + 1) * 5;

        src1_v4f[i].x = (float)(i + 1);
        src1_v4f[i].y = (float)(i + 1) * 1.1f;
        src1_v4f[i].z = (float)(i + 1) * 1.2f;
        src1_v4f[i].w = (float)(i + 1) * 1.3f;
        src2_v4f[i].x = (float)(i + 1) * 0.5f;
        src2_v4f[i].y = (float)(i + 1) * 0.6f;
        src2_v4f[i].z = (float)(i + 1) * 0.7f;
        src2_v4f[i].w = (float)(i + 1) * 0.8f;

        src1_v4i[i].x = i + 1;
        src1_v4i[i].y = (i + 1) * 2;
        src1_v4i[i].z = (i + 1) * 3;
        src1_v4i[i].w = (i + 1) * 4;
        src2_v4i[i].x = i + 10;
        src2_v4i[i].y = (i + 1) * 5;
        src2_v4i[i].z = (i + 1) * 6;
        src2_v4i[i].w = (i + 1) * 7;
    }

    // ==== Compute reference results using C fallbacks ====
    printf("Computing reference results...\n");
    mn_add_float_c(ref_f, src1_f, src2_f, count);
    mn_add_int32_c(ref_i, src1_i, src2_i, count);
    mn_add_vec2f_c(ref_v2f, src1_v2f, src2_v2f, count);
    mn_add_vec2i_c(ref_v2i, src1_v2i, src2_v2i, count);
    mn_add_vec3f_c(ref_v3f, src1_v3f, src2_v3f, count);
    mn_add_vec3i_c(ref_v3i, src1_v3i, src2_v3i, count);
    mn_add_vec4f_c(ref_v4f, src1_v4f, src2_v4f, count);
    mn_add_vec4i_c(ref_v4i, src1_v4i, src2_v4i, count);

    // ==== Test each NEON routine individually ====
    printf("Testing mn_add_float_neon...\n");
    mn_result_t result1 = mn_add_float_neon(dst_f, src1_f, src2_f, count);
    if (result1 != MN_SUCCESS) {
        printf("mn_add_float_neon failed with code %d\n", result1);
        goto cleanup;
    }

    printf("Testing mn_add_int32_neon...\n");
    mn_result_t result2 = mn_add_int32_neon(dst_i, src1_i, src2_i, count);
    if (result2 != MN_SUCCESS) {
        printf("mn_add_int32_neon failed with code %d\n", result2);
        goto cleanup;
    }

    printf("Testing mn_add_vec2f_neon...\n");
    mn_result_t result3 = mn_add_vec2f_neon(dst_v2f, src1_v2f, src2_v2f, count);
    if (result3 != MN_SUCCESS) {
        printf("mn_add_vec2f_neon failed with code %d\n", result3);
        goto cleanup;
    }

    printf("Testing mn_add_vec2i_neon...\n");
    mn_result_t result4 = mn_add_vec2i_neon(dst_v2i, src1_v2i, src2_v2i, count);
    if (result4 != MN_SUCCESS) {
        printf("mn_add_vec2i_neon failed with code %d\n", result4);
        goto cleanup;
    }

    printf("Testing mn_add_vec3f_neon...\n");
    mn_result_t result5 = mn_add_vec3f_neon(dst_v3f, src1_v3f, src2_v3f, count);
    if (result5 != MN_SUCCESS) {
        printf("mn_add_vec3f_neon failed with code %d\n", result5);
        goto cleanup;
    }

    printf("Testing mn_add_vec3i_neon...\n");
    mn_result_t result6 = mn_add_vec3i_neon(dst_v3i, src1_v3i, src2_v3i, count);
    if (result6 != MN_SUCCESS) {
        printf("mn_add_vec3i_neon failed with code %d\n", result6);
        goto cleanup;
    }

    printf("Testing mn_add_vec4f_neon...\n");
    mn_result_t result7 = mn_add_vec4f_neon(dst_v4f, src1_v4f, src2_v4f, count);
    if (result7 != MN_SUCCESS) {
        printf("mn_add_vec4f_neon failed with code %d\n", result7);
        goto cleanup;
    }

    printf("Testing mn_add_vec4i_neon...\n");
    mn_result_t result8 = mn_add_vec4i_neon(dst_v4i, src1_v4i, src2_v4i, count);
    if (result8 != MN_SUCCESS) {
        printf("mn_add_vec4i_neon failed with code %d\n", result8);
        goto cleanup;
    }

    // ==== Validate results ====
    printf("Validating results...\n");
    
    // Check float results
    for (int i = 0; i < count; i++) {
        if (dst_f[i] != ref_f[i]) {
            printf("Float test failed at %d: NEON=%.6f, Reference=%.6f\n", 
                   i, dst_f[i], ref_f[i]);
            goto cleanup;
        }
    }
    printf("Float addition test passed!\n");

    // Check int32 results  
    for (int i = 0; i < count; i++) {
        if (dst_i[i] != ref_i[i]) {
            printf("Int32 test failed at %d: NEON=%d, Reference=%d\n", 
                   i, dst_i[i], ref_i[i]);
            goto cleanup;
        }
    }
    printf("Int32 addition test passed!\n");

    // Check vec2f results
    for (int i = 0; i < count; i++) {
        if (dst_v2f[i].x != ref_v2f[i].x || dst_v2f[i].y != ref_v2f[i].y) {
            printf("Vec2f test failed at %d\n", i);
            printf("  NEON: (%.6f, %.6f)\n", dst_v2f[i].x, dst_v2f[i].y);
            printf("  Ref:  (%.6f, %.6f)\n", ref_v2f[i].x, ref_v2f[i].y);
            goto cleanup;
        }
    }
    printf("Vec2f addition test passed!\n");

    // Check vec2i results
    for (int i = 0; i < count; i++) {
        if (dst_v2i[i].x != ref_v2i[i].x || dst_v2i[i].y != ref_v2i[i].y) {
            printf("Vec2i test failed at %d\n", i);
            printf("  NEON: (%d, %d)\n", dst_v2i[i].x, dst_v2i[i].y);
            printf("  Ref:  (%d, %d)\n", ref_v2i[i].x, ref_v2i[i].y);
            goto cleanup;
        }
    }
    printf("Vec2i addition test passed!\n");

    // Check vec3f results
    for (int i = 0; i < count; i++) {
        if (dst_v3f[i].x != ref_v3f[i].x || dst_v3f[i].y != ref_v3f[i].y || dst_v3f[i].z != ref_v3f[i].z) {
            printf("Vec3f test failed at %d\n", i);
            printf("  NEON: (%.6f, %.6f, %.6f)\n", dst_v3f[i].x, dst_v3f[i].y, dst_v3f[i].z);
            printf("  Ref:  (%.6f, %.6f, %.6f)\n", ref_v3f[i].x, ref_v3f[i].y, ref_v3f[i].z);
            goto cleanup;
        }
    }
    printf("Vec3f addition test passed!\n");

    // Check vec3i results
    for (int i = 0; i < count; i++) {
        if (dst_v3i[i].x != ref_v3i[i].x || dst_v3i[i].y != ref_v3i[i].y || dst_v3i[i].z != ref_v3i[i].z) {
            printf("Vec3i test failed at %d\n", i);
            printf("  NEON: (%d, %d, %d)\n", dst_v3i[i].x, dst_v3i[i].y, dst_v3i[i].z);
            printf("  Ref:  (%d, %d, %d)\n", ref_v3i[i].x, ref_v3i[i].y, ref_v3i[i].z);
            goto cleanup;
        }
    }
    printf("Vec3i addition test passed!\n");

    // Check vec4f results
    for (int i = 0; i < count; i++) {
        if (dst_v4f[i].x != ref_v4f[i].x || dst_v4f[i].y != ref_v4f[i].y || 
            dst_v4f[i].z != ref_v4f[i].z || dst_v4f[i].w != ref_v4f[i].w) {
            printf("Vec4f test failed at %d\n", i);
            printf("  NEON: (%.6f, %.6f, %.6f, %.6f)\n", 
                   dst_v4f[i].x, dst_v4f[i].y, dst_v4f[i].z, dst_v4f[i].w);
            printf("  Ref:  (%.6f, %.6f, %.6f, %.6f)\n", 
                   ref_v4f[i].x, ref_v4f[i].y, ref_v4f[i].z, ref_v4f[i].w);
            goto cleanup;
        }
    }
    printf("Vec4f addition test passed!\n");

    // Check vec4i results
    for (int i = 0; i < count; i++) {
        if (dst_v4i[i].x != ref_v4i[i].x || dst_v4i[i].y != ref_v4i[i].y || 
            dst_v4i[i].z != ref_v4i[i].z || dst_v4i[i].w != ref_v4i[i].w) {
            printf("Vec4i test failed at %d\n", i);
            printf("  NEON: (%d, %d, %d, %d)\n", 
                   dst_v4i[i].x, dst_v4i[i].y, dst_v4i[i].z, dst_v4i[i].w);
            printf("  Ref:  (%d, %d, %d, %d)\n", 
                   ref_v4i[i].x, ref_v4i[i].y, ref_v4i[i].z, ref_v4i[i].w);
            goto cleanup;
        }
    }
    printf("Vec4i addition test passed!\n");

    printf("All addition tests passed!\n");

cleanup:
    // Free all allocated memory
    free(src1_f); free(src2_f); free(dst_f); free(ref_f);
    free(src1_i); free(src2_i); free(dst_i); free(ref_i);
    free(src1_v2f); free(src2_v2f); free(dst_v2f); free(ref_v2f);
    free(src1_v2i); free(src2_v2i); free(dst_v2i); free(ref_v2i);
    free(src1_v3f); free(src2_v3f); free(dst_v3f); free(ref_v3f);
    free(src1_v3i); free(src2_v3i); free(dst_v3i); free(ref_v3i);
    free(src1_v4f); free(src2_v4f); free(dst_v4f); free(ref_v4f);
    free(src1_v4i); free(src2_v4i); free(dst_v4i); free(ref_v4i);

    return 0;
}
