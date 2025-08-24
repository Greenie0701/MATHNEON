#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/MN_dtype.h"   // for nm_float32_t, nm_int32_t, nm_uint32_t
#include "../includes/MN_macro.h"
#include "../src/abs/MN_abs_neon.c" // or link against built object

// Reference scalar ABS for float
static void ref_abs_float(float *dst, const float *src, unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
        dst[i] = fabsf(src[i]);
}

// Reference scalar ABS for int
static void ref_abs_int(int *dst, const int *src, unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
        dst[i] = abs(src[i]);
}

int main(void)
{
    // Example sizes to test
    const unsigned int count = 10;

    // Allocate arrays
    float src_f[count], dst_f[count], ref_f[count];
    int   src_i[count], dst_i[count], ref_i[count];

    // Fill inputs with positive + negative numbers
    for (unsigned int i = 0; i < count; i++)
    {
        src_f[i] = (i % 2 == 0) ? -(float)i * 1.1f : (float)i * 1.1f;
        src_i[i] = (i % 2 == 0) ? -(int)i : (int)i;
    }

    // Run NEON versions
    mn_abs_float_neon(dst_f, src_f, count);
    mn_abs_int32_neon(dst_i, src_i, count);

    // Run scalar reference
    ref_abs_float(ref_f, src_f, count);
    ref_abs_int(ref_i, src_i, count);

    // Validate
    int pass = 1;
    for (unsigned int i = 0; i < count; i++)
    {
        if (fabsf(dst_f[i] - ref_f[i]) > 1e-6f)
        {
            printf("Float mismatch at %u: got %f expected %f\n", i, dst_f[i], ref_f[i]);
            pass = 0;
        }
        if (dst_i[i] != ref_i[i])
        {
            printf("Int mismatch at %u: got %d expected %d\n", i, dst_i[i], ref_i[i]);
            pass = 0;
        }
    }

    if (pass)
        printf("All ABS NEON tests PASSED!\n");
    else
        printf("Some ABS NEON tests FAILED!\n");

    return pass ? 0 : 1;
}
