#include "MN_dtype.h"
#include "MN_macro.h"
#include <arm_neon.h>
#include <assert.h>
#include <math.h>

/*
Input Arguments:
    dst    - Destination pointer that stores the results
    src    - Source pointer that contains user input values
    count  - Number of elements to process

Intrinsics used: 
    vld1q_f32 - NEON intrinsic to load 4 float32 values from memory
    vabsq_f32 - NEON intrinsic to compute absolute value of 4 float32 values in parallel
    vst1q_f32 - NEON intrinsic to store 4 float32 values back to memory
    fabsf - Standard C library function that calculates the absolute value of a single float.
            Used here for leftover elements when count is not a multiple of 4.
*/

mn_result_t mn_abs_float_neon(mn_float32_t *dst, mn_float32_t *src, mn_uint32_t count)
{
    // process 4 floats at a time
    mn_uint32_t blocks = count / 4;
    mn_uint32_t remain = count % 4;

    MN_ASSERT_DS;
    for (mn_uint32_t i = 0; i < blocks; i++)
    {
        float32x4_t n_src = vld1q_f32(src);   // load 4 floats
        float32x4_t n_dst = vabsq_f32(n_src); // take abs
        vst1q_f32(dst, n_dst);                // store result
        src += 4;
        dst += 4;
    }

    MN_ASSERT_DS;
    // handle leftovers (scalar or small NEON ops)
    for (unsigned int itr = 0; itr < remain; itr++)
    {
        *dst++ = fabsf(*src++);
    }

    return MN_SUCCESS;
}

