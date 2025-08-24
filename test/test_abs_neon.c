#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/MN_dtype.h"   // for nm_float32_t, nm_int32_t, nm_uint32_t
#include "../includes/MN_macro.h"
#include "../src/abs/MN_abs_neon.c" // or link against built object

int main(void)
{
    int count = 16; 

    // Allocate dynamically instead of Variable Length Arrays (VLA), MSVC doesn't supports VLA
    float* src_f = (float*)malloc(sizeof(float) * count);
    float* dst_f = (float*)malloc(sizeof(float) * count);
    float* ref_f = (float*)malloc(sizeof(float) * count);

    int* src_i = (int*)malloc(sizeof(int) * count);
    int* dst_i = (int*)malloc(sizeof(int) * count);
    int* ref_i = (int*)malloc(sizeof(int) * count);

    if (!src_f || !dst_f || !ref_f || !src_i || !dst_i || !ref_i)
    {
        fprintf(stderr, "malloc failed!\n");
        return 1;
    }

    // Fill input with test values
    for (int i = 0; i < count; i++)
    {
        src_f[i] = (i % 2 == 0 ? -1.0f : 1.0f) * (float)i;
        ref_f[i] = fabsf(src_f[i]);

        src_i[i] = (i % 2 == 0 ? -1 : 1) * i;
        ref_i[i] = abs(src_i[i]);
    }

    // Call MN int and float routines
    mn_abs_float_neon(dst_f, src_f, count);
    mn_abs_int32_neon(dst_i, src_i, count);

    // Validate the results with standard implementations
    for (int i = 0; i < count; i++)
    {
        if (fabsf(dst_f[i] - ref_f[i]) > 1e-6f || dst_i[i] != ref_i[i])
        {
            printf("Test failed at index %d\n", i);
            free(src_f); free(dst_f); free(ref_f);
            free(src_i); free(dst_i); free(ref_i);
            return 1;
        }
    }

    printf("All abs tests passed!\n");

    free(src_f); free(dst_f); free(ref_f);
    free(src_i); free(dst_i); free(ref_i);

    return 0;
}
