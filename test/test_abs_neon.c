#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/MN_dtype.h" 
#include "../includes/MN_macro.h"
#include "../src/abs/MN_abs_neon.c"

int main(void)
{
    int count = 16;

    // Allocate dynamically instead of Variable Length Arrays (VLA), MSVC doesn't supports VLA
    // ===== Flat float/int arrays =====
    float* src_f = (float*)malloc(sizeof(float) * count);
    float* dst_f = (float*)malloc(sizeof(float) * count);
    float* ref_f = (float*)malloc(sizeof(float) * count);

    int* src_i = (int*)malloc(sizeof(int) * count);
    int* dst_i = (int*)malloc(sizeof(int) * count);
    int* ref_i = (int*)malloc(sizeof(int) * count);

    // ===== Vec2 float/int arrays =====
    mn_vec2f_t* src_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* dst_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);
    mn_vec2f_t* ref_v2f = (mn_vec2f_t*)malloc(sizeof(mn_vec2f_t) * count);

    mn_vec2i_t* src_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* dst_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);
    mn_vec2i_t* ref_v2i = (mn_vec2i_t*)malloc(sizeof(mn_vec2i_t) * count);

    if (!src_f || !dst_f || !ref_f || !src_i || !dst_i || !ref_i ||
        !src_v2f || !dst_v2f || !ref_v2f || !src_v2i || !dst_v2i || !ref_v2i)
    {
        fprintf(stderr, "malloc failed!\n");
        return 1;
    }

    // ==== Fill inputs ====
    for (int i = 0; i < count; i++)
    {
        // flat float
        src_f[i] = (i % 2 == 0 ? -1.0f : 1.0f) * (float)i;
        ref_f[i] = fabsf(src_f[i]);

        // flat int
        src_i[i] = (i % 2 == 0 ? -1 : 1) * i;
        ref_i[i] = abs(src_i[i]);

        // vec2 float
        src_v2f[i].x = (i % 2 == 0 ? -1.0f : 1.0f) * (float)(i + 0.5f);
        src_v2f[i].y = (i % 3 == 0 ? -1.0f : 1.0f) * (float)(i + 1.5f);
        ref_v2f[i].x = fabsf(src_v2f[i].x);
        ref_v2f[i].y = fabsf(src_v2f[i].y);

        // vec2 int
        src_v2i[i].x = (i % 2 == 0 ? -1 : 1) * (i + 10);
        src_v2i[i].y = (i % 3 == 0 ? -1 : 1) * (i + 20);
        ref_v2i[i].x = abs(src_v2i[i].x);
        ref_v2i[i].y = abs(src_v2i[i].y);
    }

    // ==== Call NEON routines ====
    mn_abs_float_neon(dst_f, src_f, count);
    mn_abs_int32_neon(dst_i, src_i, count);
    mn_abs_vec2f_neon(dst_v2f, src_v2f, count);
    mn_abs_vec2i_neon(dst_v2i, src_v2i, count);

    // ==== Validate flat results ====
    for (int i = 0; i < count; i++)
    {
        if (fabsf(dst_f[i] - ref_f[i]) > 1e-6f || dst_i[i] != ref_i[i])
        {
            printf("Flat test failed at index %d\n", i);
            return 1;
        }
    }

    // ==== Validate vec2 results ====
    for (int i = 0; i < count; i++)
    {
        if (fabsf(dst_v2f[i].x - ref_v2f[i].x) > 1e-6f ||
            fabsf(dst_v2f[i].y - ref_v2f[i].y) > 1e-6f)
        {
            printf("Vec2f test failed at index %d\n", i);
            return 1;
        }

        if (dst_v2i[i].x != ref_v2i[i].x || dst_v2i[i].y != ref_v2i[i].y)
        {
            printf("Vec2i test failed at index %d\n", i);
            return 1;
        }
    }

    printf("All abs tests (flat + vec2) passed!\n");

    // cleanup
    free(src_f); free(dst_f); free(ref_f);
    free(src_i); free(dst_i); free(ref_i);
    free(src_v2f); free(dst_v2f); free(ref_v2f);
    free(src_v2i); free(dst_v2i); free(ref_v2i);

    return 0;
}
