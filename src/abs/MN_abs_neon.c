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

mn_result_t mn_abs_float_neon(mn_float32_t * dst, mn_float32_t * src, mn_uint32_t count)
{
    MN_ABS_DstSrc_DO_COUNT_TIMES_FLOAT_NEON(
        MN_MAINLOOP_FLOAT_NEON_ABS,  /* SIMD main loop */
        MN_SECONDLOOP_FLOAT_ABS      /* leftover elements */
    );

    return MN_SUCCESS;
}



